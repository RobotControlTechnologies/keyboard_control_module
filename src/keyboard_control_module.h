#ifndef KEYBOARD_CONTROL_MODULE_H
#define KEYBOARD_CONTROL_MODULE_H

struct AxisKey {
  system_value axis_index;
  variable_value pressed_value;
  variable_value unpressed_value;
};

class KeyboardControlModule : public ControlModule {
  ModuleInfo mi{};
  unsigned int COUNT_AXIS{0};
  AxisData **robot_axis = nullptr;
  colorPrintfModuleVA_t *colorPrintf_p = nullptr;

  bool is_error_init = false;

  std::map<std::string, system_value> axis_names;
#ifdef _WIN32
  std::map<WORD, AxisKey *> axis_keys;
  WORD last_key;
#else
  std::map<uint32_t, AxisKey *> axis_keys;
  std::string InputDevice;
  uint16_t last_key;
#endif

  std::map<system_value, AxisData *> axis;
  
  bool last_state;
  variable_value last_axis_value;
  system_value last_axis_index;

 public:
  KeyboardControlModule();

  // init
  const struct ModuleInfo &getModuleInfo();
  void prepare(colorPrintfModule_t *colorPrintf_p,
               colorPrintfModuleVA_t *colorPrintfVA_p);

  // compiler only
  AxisData **getAxis(unsigned int *count_axis);
  void *writePC(unsigned int *buffer_length);

  // intepreter - devices
  int init();
  void execute(sendAxisState_t sendAxisState);
  void final(){};

  // intepreter - program & lib
  void readPC(void *buffer, unsigned int buffer_length);

  // intepreter - program
  int startProgram(int uniq_index);
  int endProgram(int uniq_index);

  // destructor
  void destroy();
  ~KeyboardControlModule();

  void colorPrintf(ConsoleColor colors, const char *mask, ...);
};

#endif /* KEYBOARD_CONTROL_MODULE_H */