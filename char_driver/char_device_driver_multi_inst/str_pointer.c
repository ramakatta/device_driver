/* Per-device structure */
#define NUM_DEV 3 
struct sdev_dev
{
   int  id;
   char   name[16];
} *sdev_d;

struct sdev_dev *sdev_devp[NUM_DEV];

int main()
{
  int i;
  for(i=0;i<NUM_DEV;i++)
  {
    sdev_d=(struct sdev_dev*)malloc(sizeof(struct sdev_dev));
    printf("Enter id and name\n");
    scanf("%d%s", &sdev_d->id, sdev_d->name);
    sdev_devp[i] = sdev_d;
  }
  for(i=0;i<NUM_DEV;i++)
  {
    sdev_d = sdev_devp[i];	  
    printf("id:%d name:%s\n", sdev_d->id, sdev_d->name);
  }

}
