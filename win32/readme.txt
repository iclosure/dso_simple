
╔═══════════════════╗
║       ╭──────────╮       ║
║       │╖  ╓╔═╗╥╔═╕│       ║
║       │║  ║║  ║║║    │       ║
║       │╚═╝╜  ╙╨╚═╛│       ║
║       ╰──────────╯       ║
║        Project : DSC--C-sources      ║
║        Aurthor : L.K.H.              ║
║        Version : V1.0                ║
║        Data    : 09/20/2011          ║
╚═══════════════════╝

    DSOWin.dsw -- VC6++工程执行文件
    DSOWin.vcproj -- VS2008工程执行文件

    从VC6++移植Visual Studio 2008的问题解决办法总结：
    
    1、添加文件包含路径：Project->Option->C/C++->General->附加包含目录。
    2、添加自定义库文件：要在 添加文件包含路径中添加库文件路径，同时在：
       Project->Option->Linker->Input->附加依赖项：中添加路文件名称(注意，包括后缀)。
    3、解决错误：1>LINK : fatal error LNK1104: 无法打开文件“LIBC.lib”：
       在 Project->Option->Linker->命令行：中的附加选项中添加“/nodefaultlib:libc”。
    4、如果出现系统崩溃:“Microsoft@Incremental Linker 已停止工作”：
       将 Project->Option->Linker->General中的“启用增量连接”的值“是”改为“否”。
       或者直接点击“关闭程序”后在F7重新编译工程，就不会再出现这个问题了。
    5、但是经过第四中问题的修改后，可呢过会出现以下错误：
       LINK : warning LNK4075: 忽略”/EDITANDCONTINUE”(由于”/INCREMENTAL:NO”规范)
       这个问题是因为在vc6中，工程使用的增量编译。
 
       解决办法：
           1) Project->Option->C/C++->General->启动增量链接　选择　是(INCREMENTAL)
       或者:
           2) 选择项目 Project->Option->C/C++  修改 调试信息格式 为 程序数据库（/zi） 
    6、vs2008 warning C4819

       编译VC++程序的时候出现如下提示警告：

       warning C4819: The file contains a character that cannot be represented in the current code page (936). Save the file in Unicode format to prevent data loss

           因为只是一个warning，不影响正常编译，所以并没有引起大家多大的关注。我一开始的时候也是如此。但是后来出现的次数多了，发现这个警告和在程序Debug的时候
       无法停在断点，刷刷刷就过去了根本无法进行Debug。而罪魁祸首就是这个warning，改正了这个warning就能进行Debug了。

       下面讲述我是怎么消除这个警告的。

           这个警告的意思是：在该文件中有一个或多个字符不是Unicode字符！要求把这个字符变成Unicode字符。

       难题：在编译信息里并没有提示是哪个字符，或者是在哪一行里出现的该字符。查找起来非常的难，甚至是不可能的任务！

           我在网络上找了好多资料都没有找到解决方法。因为大家都不注意这个不影响编译的警告。后来在一个国外的网站上找到了解决的方法。很简单，这个方法根本不需要知道具体是哪个字符在捣鬼！

       解决方法：打开出现warning的文件，Ctrl+A全选，然后在文件菜单：file->advanced save options ，在弹出的选项中选择新的编码方式为：UNICODE codepage 1200 ，点击确定，问题就解决了。
