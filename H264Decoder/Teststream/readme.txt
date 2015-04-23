测试脚本使用方法
V1.0
by sensong 201406

使用方法：
1.本测试程序只能执行在已经root的android手机上
2.adb shell 后使用root权限在/data/下建立dec264文件夹
3.在pc端linux,执行myPush.sh，将测试码流和测试脚本push到dec264的文件夹下面
4.使用adb push将dec264的执行程序push到/data/dec264下
5.在手机侧，/data/dec264目录下执行 sh run.sh

如果在使用过程中遇到不能写入或执行问题，检查下相关文件夹/文件的属性，使用chmod添加写/执行属性。