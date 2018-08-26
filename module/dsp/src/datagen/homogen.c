
/* 函数名 ：
 * 功能：产生（a,b)区间内均匀分布的随机数
 * 输入参数：
 * 输出参数：返回一个(a,b)区间内均匀分布的随机数
 * 说明：
 * 备注：
 */
double homogen(double a,        // 给定区间的下限
				   double b,        // 给定区间的上限
				   long * seed) // 随机数种子
{
	double t;

	*seed = 2045 * (* seed) + 1;
	*seed = * seed - (* seed / 1048576) * 1048576;
	t = ( *seed) / 1048576.0;
	t = a + (b - a) * t;

	return t;
}
 