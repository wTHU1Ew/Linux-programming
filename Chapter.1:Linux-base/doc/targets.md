## ls
主要利用`opendir()`, 然后我做了个很垃圾的隐藏隐藏文件(

## cd
全称**change directory**, 所以man搜索的关键词就是这俩. cd主要使用了chrdir()这个系统调用, 但是执行了之后只能做到改变cd命令自身, 而不是整个shell会话, 因为我这个子进程没法告诉shell我要切换目录了, gpt说要利用shell脚本, 我阿巴阿巴, 超纲了, 就先不去考虑

## mkdir
`mode_t m`改了一下, 设置为0775, 要不然权限太抽象了...

## rmdir
`rmdir(argv[1])`, ~~有缺陷, 无法递归删除内部文件和文件夹~~(草, 试了一下自带的`rmdir`命令, 也是这鸟样, 那没事了)

## rm
什么都不考虑的话, 调用`remove()`即可, 参考rm-d1

### rm -r
参考rm-d2, 主要有3个难点:

1. 要先判断目录是否为空, 然后分类操作

2. 递归调用自身来删除

3. 多参数的处理, 这里我用的`getopt()`, 但不熟练, 多半参考gpt的

## mv
这里我只做了rename功能, move功能个人感觉可以`system("cp ...")` + `unlink(path)`试试看

## cp
`fopen(), snprintf(), fread(), fwrite()`将raw直接传输

## cat
`open(), read(), write()`将文本直接打印

## more
感觉和cat有点像, 但是涉及terminal翻页之类, 感觉挺麻烦就没写

## less
感觉和cat有点像, 但是涉及terminal翻页之类, 感觉挺麻烦就没写

## pwd
`getcwd()`

## **misc**
### how to use `man` quickly
`man [page] [name]`