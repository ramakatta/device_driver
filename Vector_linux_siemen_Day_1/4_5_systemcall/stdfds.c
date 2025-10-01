int main()
{
    char buf[80];
    int n;
   /* printf("Hello world\n");
    scanf("%d",&n);
   */
    write(1,"This is written to fd number1\n",10);
    write(2,"This is written to fd number2\n",34);
    write(1,"enter line of test\n",19);
    n = read(0,buf,80);
    write(1,buf,n);
}
