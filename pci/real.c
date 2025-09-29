#include <linux/module.h>
#include <linux/pci.h>
#include <linux/netdevice.h> // For networking-related APIs
#include <linux/etherdevice.h> // For Ethernet-related functions

#define DRV_NAME "realtek_eth"
enum cfg_version {
	RTL_CFG_0 = 0x00,
	RTL_CFG_1,
	RTL_CFG_2
};
#define REALTEK_VENDOR_ID  0x10EC
#define REALTEK_DEVICE_ID  0x8168 // Replace with the specific device ID you want to target

// Probe function: Called when a matching PCI device is found
static int realtek_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
    int err;
    void __iomem *ioaddr;
    u16 vendor_id;

    pr_info("%s: Realtek Ethernet device detected\n", DRV_NAME);
    pci_read_config_word(pdev, PCI_VENDOR_ID, &vendor_id);
    pr_info("%s: Realtek Ethernet device vendor id :%x\n",DRV_NAME, vendor_id);

    // Enable the PCI device
    err = pci_enable_device(pdev);
    if (err) {
        pr_err("%s: Failed to enable PCI device\n", DRV_NAME);
        return err;
    }

    // Request PCI regions
    err = pci_request_regions(pdev, DRV_NAME);
    if (err) {
        pr_err("%s: Failed to request PCI regions\n", DRV_NAME);
        goto disable_device;
    }
    pr_info("%s:pci resource length 0 %u\n", DRV_NAME, pci_resource_len(pdev, 0));
    pr_info("%s:pci resource length 2 %u\n", DRV_NAME, pci_resource_len(pdev, 2));
    pr_info("%s:pci resource length 4 %u\n", DRV_NAME, pci_resource_len(pdev, 4));

    // Map I/O memory
    ioaddr = pci_iomap(pdev, 0, pci_resource_len(pdev, 0));
    if (!ioaddr) {
        pr_err("%s: Failed to map I/O memory\n", DRV_NAME);
        err = -ENOMEM;
        goto release_regions;
    }

    pr_info("%s: I/O memory mapped at %p\n", DRV_NAME, ioaddr);

    // Set the driver-managed flag
    pci_set_drvdata(pdev, ioaddr);



    return 0;

release_regions:
    pci_release_regions(pdev);
disable_device:
    pci_disable_device(pdev);
    return err;
}

// Remove function: Called when the PCI device is removed
static void realtek_pci_remove(struct pci_dev *pdev)
{
    void __iomem *ioaddr = pci_get_drvdata(pdev);

    if (ioaddr) {
        pci_iounmap(pdev, ioaddr);
    }

    pci_release_regions(pdev);
    pci_disable_device(pdev);

    pr_info("%s: Realtek Ethernet device removed\n", DRV_NAME);
}

static const struct pci_device_id realtek_pci_ids[] = {
	{ PCI_DEVICE(PCI_VENDOR_ID_REALTEK,	0x8129), 0, 0, RTL_CFG_0 },
	{ PCI_DEVICE(PCI_VENDOR_ID_REALTEK,	0x8136), 0, 0, RTL_CFG_2 },
	{ PCI_DEVICE(PCI_VENDOR_ID_REALTEK,	0x8167), 0, 0, RTL_CFG_0 },
	{ PCI_DEVICE(PCI_VENDOR_ID_REALTEK,	0x8168), 0, 0, RTL_CFG_1 },
	{ PCI_DEVICE(PCI_VENDOR_ID_REALTEK,	0x8169), 0, 0, RTL_CFG_0 },
	{ PCI_VENDOR_ID_DLINK,			0x4300,
		PCI_VENDOR_ID_DLINK, 0x4b10,		 0, 0, RTL_CFG_1 },
	{ PCI_DEVICE(PCI_VENDOR_ID_DLINK,	0x4300), 0, 0, RTL_CFG_0 },
	{ PCI_DEVICE(PCI_VENDOR_ID_DLINK,	0x4302), 0, 0, RTL_CFG_0 },
	{ PCI_DEVICE(PCI_VENDOR_ID_AT,		0xc107), 0, 0, RTL_CFG_0 },
	{ PCI_DEVICE(0x16ec,			0x0116), 0, 0, RTL_CFG_0 },
	{ PCI_VENDOR_ID_LINKSYS,		0x1032,
		PCI_ANY_ID, 0x0024, 0, 0, RTL_CFG_0 },
	{ 0x0001,				0x8168,
		PCI_ANY_ID, 0x2410, 0, 0, RTL_CFG_2 },
	{0,},
};


MODULE_DEVICE_TABLE(pci, realtek_pci_ids);

// PCI driver structure
static struct pci_driver realtek_pci_driver = {
    .name = DRV_NAME,
    .id_table = realtek_pci_ids,
    .probe = realtek_pci_probe,
    .remove = realtek_pci_remove,
};

// Module initialization
static int __init realtek_init(void)
{
    pr_info("%s: Initializing Realtek PCI driver\n", DRV_NAME);
    return pci_register_driver(&realtek_pci_driver);
}

// Module exit
static void __exit realtek_exit(void)
{
    pr_info("%s: Exiting Realtek PCI driver\n", DRV_NAME);
    pci_unregister_driver(&realtek_pci_driver);
}

module_init(realtek_init);
module_exit(realtek_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple PCI driver for Realtek Ethernet devices");
MODULE_VERSION("1.0");

