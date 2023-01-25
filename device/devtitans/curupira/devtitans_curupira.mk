# Herda as configurações do emulador (produto sdk_phone_x86_64)
$(call inherit-product, $(SRC_TARGET_DIR)/product/sdk_phone_x86_64.mk)

# Sobrescreve algumas variáveis com os dados do novo produto
PRODUCT_NAME := devtitans_curupira
PRODUCT_DEVICE := curupira
PRODUCT_BRAND := CurupiraBrand
PRODUCT_MODEL := CurupiraModel
PRODUCT_PACKAGES += \
	smartgas_client


BOARD_SEPOLICY_DIRS += device/devtitans/curupira/sepolicy

# Smartgas AIDL Interface
PRODUCT_PACKAGES += devtitans.smartgas

# Smartgas Binder Service
PRODUCT_PACKAGES += devtitans.smartgas-service

# Device Framework Matrix (Declara que o nosso produto Curupira precisa do serviço smartgas)
DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE := device/devtitans/curupira/device_framework_matrix.xml

PRODUCT_PACKAGES += smartgas_service_client

# Manager
PRODUCT_PACKAGES += devtitans.smartgasmanager
# App
PRODUCT_PACKAGES += devtitans.smartgasapp
