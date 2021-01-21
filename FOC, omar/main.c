#include <stdio.h>
#include <stdlib.h>

int slcItem, quant;//slcItem =selected item//quant=quantity
float cost, totalPrice = 0, mnyPaid, mnyplus;//mnyPaid=money paid...mnyplus=

int menu() //to list the items in the menu func.1
{
    printf("1.Apple   \t1.00JD\n");
    printf("2.Banana  \t1.50JD\n");
    printf("3.Orange  \t2.00JD\n");
    printf("4.Salad   \t2.50JD\n");
    printf("5.Quit    \tBILL\n");//To quit the VM
    printf("ENTER NUMBER OF ITEM:  ");

    scanf("%d", &slcItem);
    return slcItem;

}

double foodSlcPrice(slcItem)//to show the item's price chosen func.2
{
    switch (slcItem)//to search for the item selected
    {
    case 1:
        printf("you have selected apple  \t1.00JD\n_____________\n\n");
        cost = 1.00;
        break;
    case 2:
        printf("you have selected Banana \t1.50JD\n_____________\n\n");
        cost = 1.50;
        break;
    case 3:
        printf("you have selected Orange \t2.00JD\n_____________\n\n");
        cost = 2.00;
        break;
    case 4:
        printf("you have selected Salad  \t2.50JD\n_____________\n\n");
        cost = 2.50;
        break;
    default://if the user chose more than 5
        printf("UnderStock\n_____________\n");
    }
    return cost;}

double itemPrice(quant)//to calculate the whole price func.3
//after asking how much does the user want's in the main()
{
    totalPrice += (cost*quant);
    return quant;
}

int main()//start the program at least once
{
    FILE* payBill;//to open a file that shows what you've chosen
    payBill = fopen("payBill.txt","w");//name of file
    if (payBill==NULL)//if the file didn't open this will be shown in the console
    {
        printf("The File Does Not Exist");
    }
    else//a normal bill that will show even if nothing was chosen
    {
        fprintf(payBill, "The Bill Is: \n\n_____________________________________\n\n");
        fprintf(payBill, "Item\tPrice\tQuantity\tTotal\n\n");
        fprintf(payBill, "_____________________________________\n\n");
    }
    do//program starting
    {
        menu();
        if (slcItem>0 && slcItem!=5)//to enter the loop
        {
            foodSlcPrice(slcItem);//the function that shows what item the user chose at the console
            if (slcItem<5)
            {
                printf("how much do you want:  ");
                scanf("%d", &quant);
                switch (slcItem)//to show the quantity that the user needs and the total needed, at the file
                {
                case 1:
                    fprintf(payBill, "Apple \t1.00JD \t %d\t\t%.2f\n\n", quant, cost*quant);
                    break;
                case 2:
                    fprintf(payBill, "Banana\t1.50JD \t %d\t\t%.2f\n\n", quant, cost*quant);
                    break;
                case 3:
                    fprintf(payBill, "Orange\t2.00JD \t %d\t\t%.2f\n\n", quant, cost*quant);
                    break;
                case 4:
                    fprintf(payBill, "Salad \t2.50JD \t %d\t\t%.2f\n\n", quant, cost*quant);
                    break;
                }
                printf("the price is %.2f\n", cost*quant);
                printf("_____________\n\n");
                itemPrice(quant);//to save the whole price
            }
        }
    }while (slcItem != 5);

    if(slcItem==5)//if the user wants to quit
    {
        printf("Thank you....\n\tQuitting..\n\t\tThe Bill is ready:)\n");
        if (totalPrice>0)//if he chosen something
        {
            printf("please pay %.2f\t", totalPrice);
            scanf("%f", &mnyPaid);
            if (mnyPaid<totalPrice)//if the user entered less than the money wanted
            {
                do
                {
                    printf("please pay more ");
                    scanf("%f", &mnyplus);
                    mnyPaid += mnyplus;
                    printf("All money paid %.2f\n..\n",  mnyPaid);
                }while(mnyPaid<totalPrice);//this will keep going until money paid == total price
            }
            if ( mnyPaid >= totalPrice)//if the money paid as wanted
            {
                printf("Thank you the change is: %.2f\n", mnyPaid-totalPrice);
            }
            if (mnyPaid >= totalPrice)
            {
                fprintf(payBill, "\n_____________________________________\n");
                fprintf(payBill, "amount requested:\t%.f\n", totalPrice);
                fprintf(payBill, "Paid money:\t\t%.2f\n", mnyPaid);
                fprintf(payBill, "Change:  \t\t%.2f", mnyPaid- totalPrice);
                fprintf(payBill, "\n_____________________________________\n");
                fprintf(payBill, "\t\t\tTHANK YOU");
                fclose(payBill);
            }
        }
        else//if the user didn't chose a thing
        {
            printf("_____________\n");
            printf("nothing to pay\n");
            fprintf(payBill, "nothing to pay \n");
            fclose(payBill);
        }
    }
    return 0;
}
