#!/usr/bin/env python2

#   Copyright 2013, Craig Chasseur
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

import base64
import optparse
import random
import sys
import string

sys.path.append("third_party")

try:
    import json
except ImportError:
    import simplejson as json

import nltk
import progressbar

# Object which writes serializes JSON objects to a file.
class JSONFileWriter(object):
    def __init__(self, outfile, pretty = False, commas = True):
        self.outfile = outfile
        self.pretty = pretty
        self.commas = commas
    def handle_object(self, obj, objid, last = False):
        if self.pretty:
            if last or not self.commas:
                print >> self.outfile, json.dumps(obj,
                                                  sort_keys=True,
                                                  indent=4)
            else:
                print >> self.outfile, json.dumps(obj,
                                                  sort_keys=True,
                                                  indent=4) + ","
        else:
            if last or not self.commas:
                print >> self.outfile, json.dumps(obj)
            else:
                print >> self.outfile, json.dumps(obj) + ","

# Encode an integer as a base32 string.
def encode_string(intval):
    return base64.b32encode(bin(intval))

# Find at least 'min_matches' words in the 'word_counts' dictionary with
# frequency nearest to 'freq'.
def find_words_by_frequency(word_counts, freq, min_matches = 10):
    inv_counts = {}
    for (word, count) in word_counts.iteritems():
        if count in inv_counts:
            inv_counts[count].append(word)
        else:
            inv_counts[count] = [word]
    delta = 0
    retval = []
    while True:
        if (freq + delta) in inv_counts:
            retval.extend(inv_counts[freq + delta])
        elif ((delta != 0)
              and (freq - delta > 0)
              and ((freq - delta) in inv_counts)):
            retval.extend(inv_counts[freq - delta])
        if len(retval) >= min_matches:
            return retval
        delta += 1

# Generate a sample object based on 'seed'. 'total_seeds' is the total number
# of objects, 'corpus' is the set of words that strings in the nested array
# will be sampled from, and 'word_counts' is a dictionary mapping words to the
# number of times they occur in generated objects (will be updated for the
# generated object).
def generate_object(seed, total_seeds, corpus, word_counts):
    obj = {}
    # Unique string.
    obj["str1"] = encode_string(seed)
    # Another unique string (corresponds to a different object's 'str1').
    obj["str2"] = encode_string((seed + total_seeds/2) % total_seeds)
    # Unique integer.
    obj["num"] = seed
    # Boolean value.
    if (seed % 2):
        obj["bool"] = True
    else:
        obj["bool"] = False

    # Dynamically-typed value. Integer in 95% of cases, string in 5%.
    if (seed % 20):
        obj["dyn1"] = seed
    else:
        obj["dyn1"] = encode_string(seed)

    # Dynamically-typed value. Integer, string, or boolean in 1/3 cases each.
    if (seed % 3) == 2:
        obj["dyn2"] = seed
    elif (seed % 3) == 1:
        obj["dyn2"] = encode_string(seed)
    else:
        if seed % 2:
            obj["dyn2"] = True
        else:
            obj["dyn2"] = False

    # Nested array of 0-7 strings sampled from 'corpus'.
    random.seed(seed)
    obj["nested_arr"] = random.sample(corpus, seed % 8)
    wordset = set(obj["nested_arr"])
    for word in wordset:
        if word not in word_counts:
            word_counts[word] = 0
        word_counts[word] = word_counts[word] + 1

    # Nested object with members referring to 'str1' and 'num' from another
    # object.
    obj["nested_obj"] = {
        "str" : encode_string((seed + total_seeds/2) % total_seeds),
        "num" : (seed + total_seeds/2) % total_seeds
    }

    # Sparse attributes. Out of 1000 possible attributes, a "cluster" of 10 is
    # defined in any given object.
    for i in range((seed % 100) * 10, ((seed % 100) + 1) * 10):
        obj["sparse_" + str(i).zfill(3)] = encode_string(seed % 11)

    # Integer with 1000 distinct values.
    obj["thousandth"] = seed % 1000

    return obj


# Generate 'num_objects' objects, feeding them to 'base_handler'. Also generate
# num_objects/1000 "extra" objects (held out to test bulk-insert), feeding them
# to 'extra_handler'.
def generate_objects(base_handler,
                     extra_handler,
                     num_objects,
                     show_pbar = False):
    corpus = [word.lower()
              for word in nltk.corpus.brown.words()
              if word not in string.punctuation]
    word_counts = {}

    seeds = range(num_objects)
    secondary_seeds = range(num_objects, num_objects + (num_objects / 1000))

    # Generate objects in random, but repeatable, order.
    random.seed(42)
    random.shuffle(seeds)
    random.shuffle(secondary_seeds)

    if show_pbar:
        widgets = ['Generating: ',
                   progressbar.Percentage(),
                   ' ',
                   progressbar.Bar(),
                   ' ',
                   progressbar.ETA()]
        pbar = progressbar.ProgressBar(
            widgets=widgets,
            maxval=(num_objects + (num_objects / 1000))).start()

    for i, seed in enumerate(seeds):
        if i == len(seeds) - 1:
            base_handler.handle_object(
                generate_object(seed, num_objects, corpus, word_counts),
                i,
                True)
        else:
            base_handler.handle_object(
                generate_object(seed, num_objects, corpus, word_counts),
                i,
                False)
        if show_pbar:
            pbar.update(i+1)

    rec_strs = find_words_by_frequency(word_counts, num_objects / 1000)

    for i, seed in enumerate(secondary_seeds):
        if i == len(seeds) - 1:
            extra_handler.handle_object(
                generate_object(seed, num_objects, corpus, {}),
                i + num_objects,
                True)
        else:
            extra_handler.handle_object(
                generate_object(seed, num_objects, corpus, {}),
                i + num_objects,
                False)
        if show_pbar:
            pbar.update(i+1)

    if show_pbar:
        pbar.finish()

    return rec_strs

# Main function. Parses command-line arguments and runs data generation tasks.
def main():
    cli_parser = optparse.OptionParser(usage="usage: %prog [options]")
    cli_parser.add_option(
        "-o",
        "--output-file",
        action="store",
        type="string",
        dest="outfile",
        default="nobench_data.json",
        metavar="FILENAME",
        help="write JSON objects to FILENAME (default: nobench_data.json)")
    cli_parser.add_option(
        "-n",
        "--objects",
        action="store",
        type="int",
        dest="num_objs",
        default=10000,
        metavar="NUMBER",
        help="how many JSON objects to generate")
    cli_parser.add_option(
        "-p",
        "--pretty-print",
        action="store_true",
        dest="pretty",
        default=False,
        help="pretty-print generated JSON objects")
    cli_parser.add_option(
        "-m",
        "--mongo",
        action="store_true",
        dest="mongo",
        default=False,
        help=("print objects line-by-line, not as an array (the format " +
              "MongoDB expects, automatically disables pretty-printing)"))

    (options, args) = cli_parser.parse_args()
    if args:
        print "Unrecognized option (use -h for help)"
        sys.exit(1)

    if options.num_objs < 1:
        print "Must generate at least 1 object"
        sys.exit(1)

    if options.mongo:
        options.pretty = False

    print >> sys.stderr, "Downloading Brown Corpus..."
    nltk.download("brown")

    outfile_name_parts = options.outfile.rsplit(".", 1)
    if len(outfile_name_parts) == 2:
        secondary_outfile_name = (outfile_name_parts[0] +
                                  "_extra" + "." + outfile_name_parts[1])
    else:
        secondary_outfile_name = outfile_name_parts[0] + "_extra"

    outfile = open(options.outfile, 'w')
    secondary_outfile = open(secondary_outfile_name, 'w')

    if not options.mongo:
        print >> outfile, "["
        print >> secondary_outfile, "["

    main_handler = JSONFileWriter(outfile, options.pretty, not options.mongo)
    extra_handler = JSONFileWriter(secondary_outfile,
                                   options.pretty,
                                   not options.mongo)

    rec_strs = generate_objects(main_handler,
                                extra_handler,
                                options.num_objs,
                                True)

    if not options.mongo:
        print >> outfile, "]"
        print >> secondary_outfile, "]"

    outfile.close()
    secondary_outfile.close()

    print ("Finished generating, recommend using one of " +
           str(rec_strs) + " for text search")

if __name__ == "__main__":
    main()
