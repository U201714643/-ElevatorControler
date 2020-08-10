#############################################################
#计算电梯的运行方向
#############################################################
.text
addi $t0,$0,3  	# $t0->$s0
addi $t1,$0,0  	# $t1->$s1
addi $t2,$0,0  	# $t2->$s2
addi $t3,$0,1  	# $t3->$s3
addi $s4,$0,2  	# $t3->$s3
LoopForever:
#---------获取数据---------
addi $s0, $zero, 1	# $s0此后会被新数据写入	
mtc0 $s0, $12		# 关中断
add $s0,$t0,$0  	# $t0->$s0
add $s1,$t1,$0  	# $t1->$s1
add $s2,$t2,$0  	# $t2->$s2
add $s3,$t3,$0  	# $t3->$s3
mtc0 $zero, $12		# 开中断
#---------计算方向---------
#首先判断寄存器s0,s1,s2是否均为0,均为0则停止
#设定$s4为0时停止，1上升，2下降
add $s6,$0,$0
or $s6,$s6,$s0
or $s6,$s6,$s1
or $s6,$s6,$s2
beq $s6,$0,Stop
#仅有本层按钮按下也是停止
addi $t8,$0,1
addi $t9,$s3,-1
sllv $t8,$t8,$t9
beq $s6,$t8,Stop
#下降则跳转
beq $s4,2,Down
Up:
addi $s4,$0,1
#电梯内部有高的楼层被按下
add $s5,$s0,$0
srlv $s5,$s5,$s3
bgtz $s5,Exit
#有高的楼层外部向上按钮被按下
add $s5,$s1,$0
srlv $s5,$s5,$s3
bgtz $s5,Exit
#有高的楼层外部向下按钮被按下
add $s5,$s2,$0
srlv $s5,$s5,$s3
bgtz $s5,Exit
#电梯改为向下运行
addi $s4,$0,2
beq $0,$0,Exit
Down:
#电梯内部有低的楼层按钮被按下
addi $s6,$0,33
sub $s7,$s6,$s3
add $s5,$s0,$0
sllv $s5,$s5,$s7
srlv $s5,$s5,$s7
bgtz $s5,Exit
#有低的楼层外部向上按钮被按下
add $s5,$s1,$0
sllv $s5,$s5,$s7
srlv $s5,$s5,$s7
bgtz $s5,Exit
#有低的楼层外部向下按钮被按下
add $s5,$s2,$0
sllv $s5,$s5,$s7
srlv $s5,$s5,$s7
bgtz $s5,Exit
#电梯改为向上运行
addi $s4,$0,1
beq $0,$0,Exit
Stop:
add $s4,$0,$0
Exit:
#---------输出运行方向---------
add $a0,$0,$s4		# 显示 $s4
addi $v0,$0,34
syscall
add $v0,$0,$0		# 恢复寄存器$v0的值
#---------死循环---------
beq $0,$0,LoopForever
#---------停机---------
syscall
