# Database Project Target
* Implementation of two modules in Sinew: Catalog and Serializer.

## 文件结构
* 代码文件放在src中，src包含Project_UI.cpp（也即项目的主函数，以及命令行UI界面），还包含所需实现模块的头文件和cpp文件。
* 资源文件放在src之外，如Sinew结构图，nobench等等。

## 执行方法
* cd src目录
* make 编译所有文件
* ./Final 执行Project_UI.cpp（主函数）
* make clean 清除.o文件 和Final

## 项目进度

* 1. 分析Sinew系统的结构，以及明确项目要实现两大功能。 （已完成）
* 2. 调整nobench，将nltk换成github上的源。 （已完成）
* 3. 使用nobench生成所需数据,nobench_data.json(10w行),nobench_data_extra.json(12行）。 （已完成）
* 4. 构建UI。 （已完成）
* 5. 完成File里面的函数。（已完成）
* 6. 完成catalog类。(已完成）
* 7. 完成Serializer类。（已完成）

![Bridge](http://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E6%A1%A5&step_word=&pn=76&spn=0&di=44734338220&pi=&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=7600&cl=2&lm=-1&st=-1&cs=3859621855%2C2817106539&os=3302671611%2C1018383402&adpicid=0&ln=1000&fr=&fmq=1436100182771_R&ic=0&s=undefined&se=&sme=0&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&objurl=http%3A%2F%2Fpic.jschina.com.cn%2F0%2F14%2F66%2F82%2F14668253_983978.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3F3fgjof_z%26e3B3fvitgw_z%26e3Bv54_z%26e3BvgAzdH3Ffyfpj4AzdH3Fda8dAzdH3F88AzdH3FdnAzdH3Fa8cn89lbb_z%26e3Bfip4s&gsm=0)
> 摇摇洁白的树枝，花语漫天飞扬

