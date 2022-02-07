#define DECLARE_FILE(name, prefix) extern "C" uint8_t _binary_##name##_start[]; extern "C" uint8_t _binary_##name##_end[]; struct prefix##name { static size_t getLength() { return _binary_##name##_end - _binary_##name##_start; } static uint8_t* getData() { return _binary_##name##_start; } };
DECLARE_FILE(MenuIcon_png,)
DECLARE_FILE(MenuIconSelected_png,)
DECLARE_FILE(de_xml,)
DECLARE_FILE(en_xml,)
DECLARE_FILE(es_xml,)
DECLARE_FILE(fr_xml,)
DECLARE_FILE(ja_xml,)
DECLARE_FILE(ko_xml,)
