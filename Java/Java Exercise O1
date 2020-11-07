//Demo class for Exercise O1
class  Demo
{
	private  double val1;						// the first data member
	private	 double val2;						// the second data member

	public void  setValues(double num1, double num2)
	{
		val1 = num1;
		val2 = num2;
	}
	public double getValue1(void)
	{
	      return (val1);
	}
	public double getValue2(void)
	{
	      return (val2);
	}
	public double  getAverage(void)
	{
   	   return(  (valu1 + valu2) / 2);
	}
}

// Use methods defined in Demo, to use number manipulation functions
import java.util.Scanner;
public class ExerciseO1 {
	static Demo addDemo(Demo item1, Demo item2)
	{
		Demo Sum = new Demo();
		Sum.setValues(item1.getValue1() + item2.getValue2(), item1.getValue1() + item2.getValue2());
		return Sum;
	}
	static void incrDemo2(Demo item)
	{
		item.setValues(item.getValue1() + 5, item.getValue2() + 5);
	}
	
	public static void main(String args[])
	{
		Demo demo = new Demo();
		Scanner input = new Scanner(System.in);
		System.out.println("Enter val1");
		double num1 = input.nextDouble();
		System.out.println("Enter val2");
		double num2 = input.nextDouble();
		demo.setValues(num1, num2);
		System.out.println("Average = " + demo.getAverage());
		Demo obj1 = new Demo();
		obj1.setValues(5, 7);
		Demo obj2 = new Demo();
		obj2.setValues(14, 9);
		Demo objR = addDemo(obj1,obj2);
		incrDemo2(obj1);
		System.out.println("objR = " + objR.getValue1() + objR.getValue2());
		System.out.println("obj1 = " + obj1.getValue1() + obj1.getValue2());
	}
}
