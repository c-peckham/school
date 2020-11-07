//Using Employee print all of the information
import java.util.Scanner;
public class Employee {
	public Employee(){
		IDNumber = 999999;
		basePay = 0.00;		
	}
private String firstName;
private String lastName;
private int IDNumber;
private Date Birthday = new Date();
private Date Hired = new Date();
private double basePay;
Scanner S = new Scanner(System.in);
void readPInfo(Scanner scan) {
	System.out.println("First Name?");
	firstName = scan.nextLine();
	System.out.println("Last Name?");
	lastName = scan.nextLine();
	System.out.println("ID number?");
	IDNumber = scan.nextInt();
	System.out.println("Birthday?");
	Birthday.inputDate(scan);
	System.out.println("Hired?");
	Hired.inputDate(scan);
}
void readPayInfo(Scanner scan) {
	System.out.println("Base pay?");
	basePay = scan.nextDouble();
}
String getPInfoString() {
	String info = "Name: " + lastName + ", " + firstName + "\n\n ID Number: " + IDNumber + "\n\n BIRTH DAY: " + Birthday.getStringDate() + "\n\n DATE HIRED: " + Hired.getStringDate() + "\n"; 
	return info;
}
void setBpay(double newBpay) {
	basePay = newBpay;
}
double getBpay() {
	return basePay;
}
double getGpay() {
	return basePay;
}
double computeTax() {
	double taxed;
	if(basePay >= 1000) 
		taxed = basePay * .2;
	else if(basePay >= 800 && basePay < 1000)
		taxed = basePay * .18;
	else if(basePay >= 600 && basePay < 800)
		taxed = basePay * .15;
	else
		taxed = basePay * .1;
	return taxed;
}
String getPayInfoString() {
	String info;
	info = " GROSS PAY: " + basePay + "\n\n TAX DEDUCTION: " + computeTax() + "\n\n NET PAY: " + computeTax() * basePay;
	return info;
}
}

//The program to print all information
import java.util.Scanner;
public class ExerciseO4 {
	public static void main(String args[])
	{
	Scanner S = new Scanner(System.in);
	Employee Default = new Employee();
	System.out.println(Default.getPInfoString());
	System.out.println(Default.getPayInfoString());
	Employee New = new Employee();
	New.readPInfo(S);
	New.readPayInfo(S);
	System.out.println(New.getPInfoString());
	System.out.println(New.getPayInfoString());
	Employee New1 = new Employee();
	New1.readPInfo(S);
	New1.readPayInfo(S);
	System.out.println(New1.getPInfoString());
	System.out.println(New1.getPayInfoString());
	Employee New2 = new Employee();
	New2.readPInfo(S);
	New2.readPayInfo(S);
	System.out.println(New2.getPInfoString());
	System.out.println(New2.getPayInfoString());
	}
}
