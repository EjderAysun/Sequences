import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;
import java.util.Arrays;
import java.util.Scanner;

class A364881 {
    // Can produce the first 1023 terms.
    public static int aFirstMethod(int n) {
        double x = n/Math.pow(2, n);
        return (int) Math.floor(x/Math.pow(10, Math.floor(Math.log10(x))));
    }
    // Can produce the first 1023 terms.
    public static String aSecondMethod(int n) {
        return String.format("%e", ((double)n)/Math.pow(2, n)).substring(0, 1);
    }
    // Can produce the first 1085 terms.
    public static int aThirdMethod(int n) {
        MathContext unl = MathContext.UNLIMITED;
        MathContext dec128 = MathContext.DECIMAL128;
        BigDecimal x_numerator = BigDecimal.valueOf(n);
        BigDecimal x_denominator = BigDecimal.valueOf(2).pow(n, unl);
        BigDecimal x = x_numerator.divide(x_denominator, unl);
        BigDecimal log_10 = new BigDecimal(Math.log10(x.doubleValue()));
        int floor = log_10.setScale(0, RoundingMode.FLOOR).intValue();
        BigDecimal pow_10 = BigDecimal.valueOf(10).pow(floor, dec128);
        BigDecimal result = x.divide(pow_10, unl);
        return result.setScale(0, RoundingMode.FLOOR).intValue();
    }

    public static int getSequenceSize(String methodName, Scanner scanner) {
        while(true) {
            try {
                System.out.print("Enter sequence size between [1-1023] for " + methodName + ": ");
                int n = scanner.nextInt();
                if(!(n >= 1 && n <= 1023) && ((methodName.equals("aFirstMethod") || (methodName.equals("aSecondMethod"))))) {
                    throw new IllegalArgumentException("The number is not between [1-1023]!");
                } else if (!(n >= 1 && n <= 1085)) {
                    throw new IllegalArgumentException("The number is not between [1-1085]!");
                }
                return n;
            } catch (IllegalArgumentException iae) {
                System.out.println(iae);
            } catch (Exception e) {
                System.out.println("Invalid input. Please enter a valid integer!");
            }
            scanner.nextLine();
        }
    }
}

class TestDrive {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int sizeForFirstList = A364881.getSequenceSize("aFirstMethod", scanner);
        int[] listForFirstMethod = new int[sizeForFirstList];
        int sizeForSecondList = A364881.getSequenceSize("aSecondMethod", scanner);
        String[] listForSecondMethod = new String[sizeForSecondList];
        int sizeForThirdList = A364881.getSequenceSize("aThirdMethod", scanner);
        int[] listForThirdMethod = new int[sizeForThirdList];

        scanner.close();
        
        for (int n = 1; n <= sizeForFirstList; n++) {
            listForFirstMethod[n-1] = A364881.aFirstMethod(n);
        }
        for (int n = 1; n <= sizeForSecondList; n++) {
            listForSecondMethod[n-1] = A364881.aSecondMethod(n);
        }
        for (int n = 1; n <= sizeForThirdList; n++) {
            listForThirdMethod[n-1] = A364881.aThirdMethod(n);
        }

        System.out.println("results for first method:");
        System.out.println(Arrays.toString(listForFirstMethod));
        System.out.println("results for second method:");
        System.out.println(Arrays.toString(listForSecondMethod));
        System.out.println("results for third method:");
        System.out.println(Arrays.toString(listForThirdMethod));
    }
}