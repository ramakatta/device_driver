#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mod_devicetable.h>
#include <linux/property.h>
#include <linux/platform_device.h>
#include <linux/of_device.h>

static int dt_probe(struct platform_device *pdev);
static void dt_remove(struct platform_device *pdev);

static struct of_device_id my_driver_ids[] = {
              {
		      .compatible = "brightlight,mydev",
              }, {}
};
MODULE_DEVICE_TABLE(of, my_driver_ids);

static struct platform_driver my_driver = {
	.probe = dt_probe,
	.remove = dt_remove,
	.driver = {
		 .name = "my_device_driver",
		 .of_match_table = my_driver_ids,
		},
};

static int dt_probe(struct platform_device *pdev) {
           struct device *dev = &pdev->dev;
	   const char *label;
	   int my_value, ret;
	   printk("dt_probe - Now I am in probe function\n");

	   if(!device_property_present(dev, "label")) {
		   printk("dt_probe - Error! Device property label not found\n");
		   return -1;
	   }
	   if(!device_property_present(dev, "my_value")) {
		   printk("dt_probe - Error! Device property my_value not found\n");
		   return -1;
	   }
	   ret = device_property_read_string(dev,"label", &label);
	   if(ret)
	   {
		   printk("dt_probe - Error! Could not read property label \n");
		   return -1;
	   }
	   printk("dt_probe -lable:%s\n",label);
	   ret = device_property_read_u32(dev,"my_value", &my_value);
	   if(ret)
	   {
		   printk("dt_probe - Error! Could not read property my_value \n");
		   return -1;
	   }
	   printk("dt_probe -my_value:%d\n", my_value);
	   return 0;
}

static void dt_remove(struct platform_device *pdev) {
	printk("dt_probe - Now Im in remove function\n");
}
#if 0

static int __init dt_init(void)
{
    printk("dt_probe - Loading the driver ...\n");
    if(platform_driver_register(&my_driver)) {
	    printk("dt_probe - Error could not load driver \n");
	    return -1;
    }
    return 0; 
}
static void __exit dt_exit(void)
{
    printk("dt_probe - Unload driver\n");
    platform_driver_unregister(&my_driver);
}
#endif

module_platform_driver(my_driver);


//module_init(dt_init);
//module_exit(dt_exit); 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMA");
MODULE_DESCRIPTION("A simple device tree overlay module.");


