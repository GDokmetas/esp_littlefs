#include "littlefs/lfs.h"
#include "esp_littlefs.h"
#include "littlefs_api.h"

//TODO: Bu kısma flash fonksiyonlarını ekle.
int littlefs_ext_flash_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size) 
{
    esp_littlefs_t * efs = c->context;
    size_t part_off = (block * c->block_size) + off;
    esp_err_t err = esp_flash_read(efs->ext_flash, buffer, part_off, size);
    if (err) {
        ESP_LOGE(ESP_LITTLEFS_TAG, "failed to read addr %08x, size %08x, err %d", (unsigned int) part_off, (unsigned int) size, err);
        return LFS_ERR_IO;
    }
    return 0;
}

int littlefs_ext_flash_write(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) 
{
    esp_littlefs_t * efs = c->context;
    size_t part_off = (block * c->block_size) + off;
    esp_err_t err = esp_flash_write(efs->ext_flash, buffer, part_off, size);
    if (err) {
        ESP_LOGE(ESP_LITTLEFS_TAG, "failed to write addr %08x, size %08x, err %d", (unsigned int) part_off, (unsigned int) size, err);
        return LFS_ERR_IO;
    }
    return 0;
}

int littlefs_ext_flash_erase(const struct lfs_config *c, lfs_block_t block) 
{
    esp_littlefs_t * efs = c->context;
    size_t part_off = block * c->block_size;
    esp_err_t err = esp_flash_erase_region(efs->ext_flash, part_off, c->block_size);
    if (err) {
        ESP_LOGE(ESP_LITTLEFS_TAG, "failed to erase addr %08x, size %08x, err %d", (unsigned int) part_off, (unsigned int) c->block_size, err);
        return LFS_ERR_IO;
    }
    return 0;
}

int littlefs_esp_ext_flash_sync(const struct lfs_config *c) 
{
    /* Unnecessary for esp-idf */
    return LFS_ERR_OK;
}
