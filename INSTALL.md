#
安装官方版本

假设LightGBM.tz所在的目录为XXX
```
cd XXX
tar -xvf LightGBM.tz
cd LightGBM
mkdir build;cd build
cmake -DOFFICIAL=1 ..
sudo make install
```
cmake -DOFFICIAL=1 意为编译官方版本，否则编译定制版本。
至此,已经安装完毕官方版本的LightGBM,我们使用官方版本的LightGBM训练模型，获取模型参数，然后改写预测逻辑。

# 训练模型
官方给出了一个多分类的样例,里面可以观察到LightGBM所支持的特征向量数据格式。
```
cd XXX/LightGBM
cd examples/multiclass_classification
lightgbm conf=train.conf
```
训练结束后，可以生成模型参数文件：LightGBM_Model.txt,该文件
在模型预测时会被载入。
然后 使用官方版本的lightgbm预测一下：
ligthgbm 会先载入模型，然后读取预测样本，接着计算结果，最后再将结果写入文件。

```
lightgbm conf=predict.conf
```


该命令会生成预测结果：LightGBM_predict_result.txt

#使用定制版本

之所以要改写预测逻辑，主要因为官方给出的版本只支持从文件读取待预测样本，为了能够接收实时数据并预测 我们需要改写预测逻辑。
改写的方式有两种：
1.将实时数据保存成文件，然后再使用开启一个子进程使用官方编写的lightgbm进行预测。然后再读取预测结果文件。
该方法的优点：无需再次实现预测模块，预测结果可靠性有保障
缺点：频繁IO,而且每次子进程运行lightgbm这个二进制文件，都会重新建立模型。此处耗时大。虽然IO可以使用管道机制加速···
2.重写预测逻辑，模型只载入一次;可通过其它IPC方式接收数据。
优点：预测速度快；
缺点：**结果可靠性需要检验；尤其是LightGBM使用多处理开发技术，当前改写的版本可能存在一定的bug**。

定制的代码在XXX/LightGBM/src/predictgbm.cpp上，
为了添加新功能，我们只需要在这个文件添加即可。

目前该文件实现了载入模型参数，并对样本进行预测的功能，虽然现阶段
样本是硬编码的，但是只需添加通过IPC接收实时待预测样本的逻辑即可实现实时预测功能。
编译方式：
```
cd XXX/LightGBM
cd build
cmake -DOFFICIAL=0 ..
sudo make install
```
该过程会生成predictgbm 可执行文件，该文件的main函数就在XXX/LightGBM/src/predictgbm.cpp。

然后我们转到刚刚那个多分类样例的文件夹
```
cd XXX/LightGBM
cd examples/multiclass_classification
predictgbm
```
predictgbm会载入当前文件夹下的LightGBM_model.txt模型参数文件，以及predict.conf文件（该文件没有多大用处，只是为了方便使用官方库函数），然后在程序中预测。
在本机的测试中：
测试2^20，约100w条样本，每条样本为27维，大约花费21s。平均每秒
5W条样本。
机器配置：
CPU:Intel(R) Xeon(R) CPU E5-2620 v4 @ 2.10GHz 4核，32 G内存


