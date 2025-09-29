#include <stdio.h>
#include <stdlib.h>
#include <tss2/tss2_esys.h>

#define BUFFER_SIZE 4096

int main() {
    TSS2_RC rc;
    ESYS_CONTEXT *ctx;
    TPM2_CAP capability = TPM2_CAP_TPM_PROPERTIES;
    UINT32 property = TPM2_PT_FIXED;
    UINT32 propertyCount = TPM2_MAX_TPM_PROPERTIES;
    TPMS_CAPABILITY_DATA *capabilityData;

    // Initialize the ESAPI context
    rc = Esys_Initialize(&ctx, NULL, NULL);
    if (rc != TSS2_RC_SUCCESS) {
        fprintf(stderr, "Esys_Initialize: 0x%x\n", rc);
        return 1;
    }

    // Get the capability data
    rc = Esys_GetCapability(ctx, ESYS_TR_NONE, ESYS_TR_NONE, ESYS_TR_NONE,
                            capability, property, propertyCount, NULL, &capabilityData);
    if (rc != TSS2_RC_SUCCESS) {
        fprintf(stderr, "Esys_GetCapability: 0x%x\n", rc);
        Esys_Finalize(&ctx);
        return 1;
    }

    // Create a buffer to store the output
    char buffer[BUFFER_SIZE];
    int offset = 0;

    // Process the capability data
    if (capabilityData->capability == TPM2_CAP_TPM_PROPERTIES) {
        TPML_TAGGED_TPM_PROPERTY properties = capabilityData->data.tpmProperties;
        for (size_t i = 0; i < properties.count; i++) {
            offset += snprintf(buffer + offset, BUFFER_SIZE - offset, "Property: 0x%x, Value: 0x%x\n",
                               properties.tpmProperty[i].property, properties.tpmProperty[i].value);
        }
    }

    // Print the buffer
    printf("%s", buffer);

    // Clean up
    Esys_Free(capabilityData);
    Esys_Finalize(&ctx);

    return 0;
}

