//Using Date, see if a project is on time, early or late
import java.util.Scanner;
public class Date {
	public Date() {
	Month = 1;
	Day = 1;
	Year = 1960;
	checkDate(Month, Day, Year);
	}
	int Month, Day, Year;
	private void checkDate(int Month, int Day, int Year)
	{
		if(Month <= 0 || Month >= 13) {
			System.exit(1);
		}
		else if(Month == 9 || Month == 4 || Month == 6 || Month == 11) 
		{
			if(Day <= 0 || Day >= 31)
				{
				System.exit(1);
				}
		}
		else if(Month == 2)
		{
			if(Day <= 0 || Day >= 29) {
				System.exit(1);		
			}
		}
		else if(Year < 1960 || Year > 2016)
		{
			System.exit(1);
		}
	}
	public void inputDate(Scanner scan)
	{
		scan = new Scanner(System.in);
		System.out.println("Enter Month");
		Month = scan.nextInt();
		System.out.println("Enter Day");
		Day = scan.nextInt();
		System.out.println("Enter Year");
		Year = scan.nextInt();		
	}
	public String getStringDate()
	{
		String month = "" + Month;
		String day = "" + Day; 
		String year = "" + Year;
		String date = month + "/" + day + "/" + year;
		return date;
	}
	public boolean isEqualTo(Date obj)
	{
		if(Month == obj.Month && Day == obj.Day && Year == obj.Year)
			return true;
		else 
			return false;
	}
	public int getMonth()
	{
		return Month;
	}
	public int getDay()
	{
		return Day;
	}
	public int getYear()
	{
		return Year;
	}
	public boolean isGreaterThan(Date obj1, Date obj2)
	{
		if(obj1.Year >= obj2.Year && obj1.Month>= obj2.Month && obj1.Day > obj2.Day)
			return true;
		else
			return false;
	}
}

//Determines if project is on time, late or early
import java.util.Scanner;
public class ExerciseO3 {
	public static void main(String args[])
	{
		Scanner S = new Scanner(System.in);
		Date obj = new Date();
		System.out.println(obj.getStringDate());
		Date today = new Date();
		today.inputDate(S);
		System.out.println("Today's date is:\t" + today.getStringDate());
		Date dueDate = new Date();
		dueDate.Day = 31;
		dueDate.Month = 9;
		dueDate.Year = 2019;
		if(dueDate.isEqualTo(today))
		{
			System.out.println("Your project is on time");
		}
		else if(dueDate.isGreaterThan(today, dueDate))
		{
			System.out.println("Your project is late");
		}
		else if(today.isGreaterThan(dueDate, today))
		{
			System.out.println("Your project is early");			
		}
		Date inValid = new Date();
		inValid.Day = 45;
		inValid.Month = 12;
		inValid.Year = 1900;
	}
}
