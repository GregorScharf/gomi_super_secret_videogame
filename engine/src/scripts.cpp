#include "../include/scripts.hpp"
#include "types.hpp"

void generate_new_script(string name) {
  ofstream file(name);

  if (file.is_open()) {

    file << "#include \"types.hpp\"\n#include\"scripts.hpp\"\n\n class " << name
         << ": script {\n public: \n \n void start() override {} \n\n void "
            "update() override \n\n}"
         << endl;
    file.close();
  }
}
