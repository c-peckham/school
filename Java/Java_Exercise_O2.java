//Use Demo for Exercise O2
public class Demo {
		private  double val1;						// the first data member
		private	 double val2;						// the second data member
		public void  setValues(double num1, double num2)
		{
			val1 = num1;
			val2 = num2;
		}
		public double getValue1()
		{
		      return (val1);
		}
		public double getValue2()
		{
		      return (val2);
		}
		public double  getAverage()
		{
	   	   return(  (val1 + val2) / 2);
		}
		public void decrDemo(Demo obj)
		{
			obj.val1 = obj.val1 - 1;
			obj.val2 = obj.val2 - 1;
		}
}

//Data manipulation program using Demo
import java.util.Scanner;
public class ExerciseO2 {
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
			Demo obj1 = new Demo();
			obj1.setValues(5, 7);
			obj1.decrDemo(obj1);
			System.out.println("obj1 = " + obj1.getValue1() + " , " + obj1.getValue2());
		}
	}
