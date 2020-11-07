// Input a given number of test scores and print the results and a comment based off the results

//Main program
import java.util.Scanner;
public class ExerciseI3 {
			public static void main(String []args){
				Scanner S = new Scanner(System.in);
				int TestNumber;
				double[] scores;
				System.out.println("How many Scores?");
			TestNumber = S.nextInt();
			scores = ExerciseI3Methods.readTestScores(TestNumber);
			ExerciseI3Methods.printTestResults(scores);
			
		}
}

//Methods used in Main program
public class ExerciseI3Methods {
		
		static void printComment(char grade) {
			switch(grade) {
			case 'A':	System.out.println("   very good");
			break;
			case 'B':	System.out.println("   good");
			break;
			case 'C':	System.out.println("   satisfactory");
			break;
			case 'D':	System.out.println("   need improvement");
			break;
			case 'F':	System.out.println("   poor");
			break;
			default :	System.out.println(" ");
			break;
			}
		}
		
		static double[] readTestScores(int size)
		{
			Scanner S = new Scanner(System.in);
			double[] Scores = new double[size];
			System.out.println("Input Test Scores");
			for(int i = 0; i < size; i++)
			{
				Scores[i] = S.nextDouble();
			}
			return Scores;
		}
		
		static char getLetterGrade(double score)
		{
			if(score >= 90)
				return 'A';
			else if (score >= 80 && score <90)
				return 'B';
			else if (score >= 70 && score <80)
				return 'C';
			else if (score >= 60 && score <70)
				return 'D';
			else 
				return 'F';
		}
		
		static void printTestResults(double[] testList)
		{
			
			System.out.printf("%-10s %-10s %-10s\n", "Test Score", "Letter Grade", "Comment");
			for(int i = 0; i < testList.length; i++)
			{
				System.out.printf("%-10.2f %-10C", testList[i], getLetterGrade(testList[i]));
				printComment(getLetterGrade(testList[i]));
			}
		}
}
