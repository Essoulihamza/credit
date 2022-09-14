#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BASE 10
int number_digits( unsigned long long int integer ); //function that return the number of digits in an integer.
int verification(char* ccn);
int main(void)
{
    char CreditCardNumber[17];
    char *end;
    //take input from user.
    do{
        printf("Enter your credit card number: ");
        gets(CreditCardNumber);
    }while( strlen(CreditCardNumber) > 16 || strlen(CreditCardNumber) < 13 || verification(CreditCardNumber) < strlen(CreditCardNumber) );
    //
    unsigned long long int credit_card_number = strtoull(CreditCardNumber, &end, BASE);
    int last_digit; //store a digit every loop.
    int credit_card_number_digits = number_digits(credit_card_number); // store the number of digits in the credit card number.
    int digits[credit_card_number_digits];  //an array that store the seperated digits of the credit card number. 
    int checksum = 0;  //store the sum of digits by a way that we can figure out whether it is a valid credit card or not.    
    for ( int i = 0; i < credit_card_number_digits; i++ ) //select all digits and insert them in an array.
    {
        last_digit = credit_card_number % 10;
        credit_card_number = ( credit_card_number - last_digit ) / 10;    
        digits[credit_card_number_digits - i - 1] = last_digit;
    }
    for( int i = credit_card_number_digits - 2; i >= 0; i-=2 ) // multipy by 2 any other digit starting with the last second one.
    {
        int mult = number_digits( (digits[i]*2) );
        if( mult == 1 )
        {
            checksum += digits[i] * 2;
        }
        else if( mult == 2 )
        {
            int first = ( digits[i] * 2 ) %  10;
            int second = ( ( digits[i] * 2 ) - first ) / 10;
            checksum += ( first + second );
        }
    }
    for( int i = credit_card_number_digits - 1; i >0; i-=2 ) // add the inmultipyed digits to the checksum...
    {
        checksum += digits[i];
    }
    if(  checksum % 10 == 0 ) // check whether it's a valid credit card or not, and figure out the type of it.
    {
        int first_digits =  (digits[0] * 10) + digits[1];
        if( credit_card_number_digits == 15 && first_digits  == 34 || first_digits  == 37 )
            printf("This is an American Express credit card.\n");
        else if( credit_card_number_digits == 16 && first_digits  == 51 || first_digits  == 52 || first_digits  == 53 || first_digits == 54 || first_digits == 55 )
            printf("This is an Master Card credit card.\n");
        else if( credit_card_number_digits == 16 || credit_card_number_digits == 13  && first_digits == 4 )
            printf("This is an Visa card.\n");
        else printf("This credit card doesn't exist!!\n");
    }
    else printf("Invalid credit card number.");
}
int number_digits( unsigned long long int credit_card_number ) //function that get the number of the digits in any integer.
{
    int digits = 0;
    while ( credit_card_number > 0)
    {
        credit_card_number /= 10;
        digits++;
    }
    return digits;
}
int verification(char* ccn)
{
    int lenght = strlen(ccn);
    int count = 0;
    for( int i = 0; i < lenght; i++ )
    {
        if( isdigit(ccn[i]) != 0 )
            count++;
    }
    return count;
}
