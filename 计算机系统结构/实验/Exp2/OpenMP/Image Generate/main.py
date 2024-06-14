import numpy as np
import matplotlib.pyplot as plt

# 设置字体
font1 = {
    'weight': 'bold',
    'size': 20,
}

font2 = {
    'weight': 'normal',
    'size': 17,
}

# 设置y轴真实数据
SerialTime = [2.40,
              2.40, 2.40, 2.40, 2.40, 2.40,
              2.40, 2.40, 2.40, 2.40,
              2.40, 2.40]
ParallelTime = [2.416, 1.556, 0.956, 0.978, 1.029,
                0.96799, 0.9323, 0.91154, 0.8841, 0.9930,
                1.043, 1.317]
Speedup = [1.0041, 1.559, 2.538, 2.480, 2.3569, 2.507, 2.60296, 2.6623, 2.7447, 2.4438,
           2.3258, 1.84133]

# 设置x轴名称
xlabel = 'Thread Num'
# 设置y轴名称
ylabel = 'Time Cost[ms]/Rate'
# 图标名称
# title = '3000×3000 Matrix Multiplication'

# 设置x轴显示值
# a有四个值，将均匀的显示1.2.3.4四个值
# x内为想要显示的值，即坐标经后面的代码会修改为4.16.64.128
# a = [1,2,4,8,16,32]
X_Num = [r'$2^{0}$', r'$2^{1}$', r'$2^{2}$', r'$2^{3}$', r'$2^{4}$', r'$2^{5}$', r'$2^{6}$', r'$2^{7}$', r'$2^{8}$',
         r'$2^{9}$', r'$2^{10}$', r'$2^{11}$']
# X_Num = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024]

# 创建一张图像为9：6
fig = plt.figure(figsize=(9, 6))
# 为图像添加子目标ax2,后续所有的操作为在ax2上操作
ax2 = fig.add_subplot()

# 设置图例名称
Serial_Label = 'Serial Time'
Parallel_Label = 'Parallel Time'
Speed_Label = 'Speedup'

# 设置四个y代表的真实数据
y1 = SerialTime
y2 = ParallelTime
y3 = Speedup

# 添加图例
ax2.plot(X_Num, y1, c='mediumseagreen', linewidth=2, label=Serial_Label)
ax2.plot(X_Num, y2, c='cornflowerblue', linewidth=2, label=Parallel_Label)
ax2.plot(X_Num, y3, c='indianred', linewidth=2, label=Speed_Label)

# 设置图例字体
plt.legend(prop={'size': 17})

# 分别将y1-y4在图标中画出折线图,a为x四个点的值，y1为y四个点的值，c代表颜色，linewidth代表折线粗细
ax2.plot(X_Num, y1, c='mediumseagreen', linewidth=4)
ax2.plot(X_Num, y2, c='cornflowerblue', linewidth=4)
ax2.plot(X_Num, y3, c='indianred', linewidth=4)

# 设置x轴，y轴，及图表标题名称及字体
# ax2.set_title(title, font1)
ax2.set_xlabel(xlabel, font2)
ax2.set_ylabel(ylabel, font2)

# 将x轴坐标刻度1.2.3.4替换为我们想要的4.16.64.128
ax2.xaxis.set_ticks(X_Num)
# 设置刻度数字大小
ax2.tick_params(which='minor', length=0)
ax2.tick_params(labelsize=14)

# 设置坐标刻度大小
# ax2.tick_params(axis='x',width=1,fontsize=1)

# 画点，将四个点显著标记
ax2.plot(X_Num, y1, 'o', markersize=5, color='darkslategray')
ax2.plot(X_Num, y2, 'o', markersize=5, color='darkslategray')
ax2.plot(X_Num, y3, 'o', markersize=5, color='darkslategray')

# 存储
plt.savefig("./PI_Thread_Time.jpg")
# 显示
plt.show()
