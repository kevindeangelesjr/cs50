#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long card_num = get_long("Number: ");

    int length = 0;
    long num = card_num;
    while (num != 0)
    {
        num /= 10;
        length++;
    }

    int next_digit;
    int first_digit = 0;
    int second_digit = 0;
    int counter = 1;
    int total_odd_digits = 0;
    int total_even_digits = 0;
    num = card_num;

    while (counter <= length)
    {
        next_digit = num % 10;
        num /= 10;

        if (counter == length)
        {
            first_digit = next_digit;
        }
        else if (counter == (length - 1))
        {
            second_digit = next_digit;
        }

        if (counter % 2 == 0)
        {
                int product = next_digit * 2;
                int product_position = product;
                int product_length;

                    while (product_position != 0)
                    {
                        product_position /= 10;
                        product_length++;
                    }
                
                int product_counter = 1;
                int next_product_digit;
                while (product_counter <= product_length)
                {
                    next_product_digit = product % 10;
                    product /= 10;

                    total_even_digits += next_product_digit;

                    product_counter++;
                }
        }
        else
        {
            total_odd_digits += next_digit;
        }
        
        counter++;
    }

    int checksum = total_odd_digits + total_even_digits;
    string status;
    if (checksum % 10 == 0)
    {
        if ((length == 15 && first_digit == 3) && second_digit == 4 || second_digit == 7)
        {
                status = "AMEX";
        }
        else if ((length == 16 && first_digit == 5) && (second_digit == 1 || second_digit == 2 || second_digit == 3 || second_digit == 4 || second_digit == 5))
        {
                status = "MASTERCARD";
        }
        else if ((length == 13 && first_digit == 4) || (length == 16 && first_digit == 4))
        {
                status = "VISA";
        }
        else
        {
            status = "INVALID";
        }
        
    }
    else
    {
        status = "INVALID";
    }
    
    printf("%s\n", status);
}