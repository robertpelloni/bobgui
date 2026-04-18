import re

with open('bobgui/meson.build', 'r') as f:
    content = f.read()

pattern = r"'cpp/tools_subsystems\.hpp',"
replacement = r"'cpp/tools_subsystems.hpp',\n  'cpp/module/tools_pillar.hpp',"
content = re.sub(pattern, replacement, content)

pattern2 = r"'cpp/core_subsystems\.hpp',"
replacement2 = r"'cpp/core_subsystems.hpp',\n  'cpp/tools_subsystems.hpp',"
content = re.sub(pattern2, replacement2, content)

with open('bobgui/meson.build', 'w') as f:
    f.write(content)
