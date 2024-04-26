#pragma once

#define QOSMETICS_CORE_EXPORT __attribute__((visibility("default")))

#ifdef __cplusplus
#define QOSMETICS_CORE_EXPORT_FUNC extern "C" QOSMETICS_CORE_EXPORT
#else
#define QOSMETICS_CORE_EXPORT_FUNC QOSMETICS_CORE_EXPORT
#endif
