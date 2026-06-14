void even(void)
{
     printf("it is even\n");
}

void odd(void)
{
     printf("it is odd\n");
}
int main()
{
     int i;
     for (i = 0; ;i++) {
          if (i % 2)
               odd();
          else
               even();
     }
}
