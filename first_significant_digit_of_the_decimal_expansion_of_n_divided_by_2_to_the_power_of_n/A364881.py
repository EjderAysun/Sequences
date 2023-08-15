from math import pow, floor, log10

class A364881(ValueError):
    # Can produce the first 1023 terms.
    @staticmethod
    def a_first_method(n):
        x = n/pow(2, n)
        return floor(x/pow(10, floor(log10(x))))
    
    # Can produce the first 1023 terms.
    @staticmethod
    def a_second_method(n) : return "{:e}".format(n/(2**n))[0]

    @staticmethod
    def get_sequence_size(methodName):
        while(True):
            try:
                n = int(input("Enter sequence size between [1-1023] for %s: " %methodName))
                if (n >= 1 and n <= 1023) is False:
                    raise A364881("The number is not between [1-1023]!")
                return n
            except A364881 as ise:
                print(ise)
            except Exception:
                print("Invalid input. Please enter a valid integer!")

def test_drive():
    size_for_first_list = A364881.get_sequence_size(A364881.a_first_method.__name__)
    list_for_first_method = list()
    size_for_second_list = A364881.get_sequence_size(A364881.a_second_method.__name__)
    list_for_second_method = list()

    for n in range(1, size_for_first_list):
        list_for_first_method.append(A364881.a_first_method(n))
    for n in range (1, size_for_second_list):
        list_for_second_method.append(A364881.a_second_method(n))

    print("results for first method: %s" %list_for_first_method)
    print("results for second method: %s" %list_for_second_method)

if __name__ == "__main__":
    test_drive()