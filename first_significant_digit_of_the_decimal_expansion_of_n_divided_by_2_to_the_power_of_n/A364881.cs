class A364881  {
    // Can produce the first 1023 terms.
    public static int aFirstMethod(int n) {
        double x = n/Math.Pow(2, n);
        return (int)Math.Floor(x / Math.Pow(10, Math.Floor(Math.Log10(x))));
    }
    // Can produce the first 1023 terms.
    public static string aSecondMethod(int n) {
        return string.Format("{0:e}", ((double)n)/Math.Pow(2, n)).Substring(0, 1);
    }

    public static int getSequenceSize(String methodName) {
        while(true) {
            try {
                Console.Write("Enter sequence size between [1-1023] for " + methodName + ": ");
                int n = Convert.ToInt32(Console.ReadLine());
                if(!(n >= 1 && n <= 1023)) {
                    throw new ArgumentOutOfRangeException();
                }
                return n;
            } catch (ArgumentOutOfRangeException) {
                Console.WriteLine("The number is not between [1-1023]!");
            } catch (Exception) {
                Console.WriteLine("Invalid input. Please enter a valid integer!");
            }
        }
    }
}

class TestDrive {
    static void Main(String[] args) {
        
        int sizeForFirstList = A364881.getSequenceSize("aFirstMethod");
        int[] listForFirstMethod = new int[sizeForFirstList];
        int sizeForSecondList = A364881.getSequenceSize("aSecondMethod");
        string[] listForSecondMethod = new string[sizeForSecondList];
        
        for (int n = 1; n <= sizeForFirstList; n++) {
            listForFirstMethod[n-1] = A364881.aFirstMethod(n);
        }
        for (int n = 1; n <= sizeForSecondList; n++) {
            listForSecondMethod[n-1] = A364881.aSecondMethod(n);
        }

        Console.WriteLine("results for first method:");
        Console.WriteLine(string.Join(", ", listForFirstMethod));
        Console.WriteLine("results for second method:");
        Console.WriteLine(string.Join(", ", listForSecondMethod));
    }
}