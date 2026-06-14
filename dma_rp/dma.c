#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/slab.h>
#include <linux/dma-map-ops.h> // Required for arch_setup_dma_ops

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Developer");
MODULE_DESCRIPTION("DMA Coherent Allocation Example");
MODULE_VERSION("1.0");

#define ALLOC_SIZE 4096  // Allocate 1 page (4KB)

static struct device *dummy_dev;
static void *virt_addr;
static dma_addr_t dma_handle;

static int __init dma_mod_init(void)
{
   pr_info("DMA Initilaization");
   dummy_dev = root_device_register("dma_dummy");
   if(IS_ERR(dummy_dev))
   {
       pr_err("DMA device registeration failed\n");
       return PTR_ERR(dummy_dev);
   }

    // Force setup the architecture-specific DMA operations for the dummy device
    arch_setup_dma_ops(dummy_dev, false);

    // Configure DMA mask to specify addressable memory range (64-bit)
    if (dma_set_mask_and_coherent(dummy_dev, DMA_BIT_MASK(64))) {
        pr_err("DMA Mod: No suitable DMA configuration available\n");
        root_device_unregister(dummy_dev);
        return -EIO;
    }

   virt_addr = dma_alloc_coherent(dummy_dev, ALLOC_SIZE, &dma_handle, GFP_KERNEL);
   if(!virt_addr)
   {
      pr_err("dma memory allocation failed\n");
      root_device_unregister(dummy_dev);
      return PTR_ERR(virt_addr);
   }

   phys_addr_t actual_pa = virt_to_phys(virt_addr);
   // Print the requested addresses to dmesg
    pr_info("DMA Mod: Allocation successful!\n");
    pr_info("DMA Mod: Virtual Address  = %p\n", virt_addr);
      pr_info("DMA Mod: PA Address  = %pa\n", &actual_pa);
    pr_info("DMA Mod: Physical (DMA) Address = %pad\n", &dma_handle);

    return 0;
}

static void __exit dma_mod_exit(void)
{
    if (virt_addr) {
        dma_free_coherent(dummy_dev, ALLOC_SIZE, virt_addr, dma_handle);
        pr_info("DMA Mod: Coherent buffer freed\n");
    }
    
    if (dummy_dev) {
        root_device_unregister(dummy_dev);
        pr_info("DMA Mod: Dummy device unregistered\n");
    }
    
    pr_info("DMA Mod: Module exited\n");
}   





module_init(dma_mod_init);
module_exit(dma_mod_exit);