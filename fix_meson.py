import re

with open('bobgui/meson.build', 'r') as f:
    content = f.read()

pattern = r"'cpp/command_palette\.hpp',"
replacement = r"'cpp/command_palette.hpp',\n  'cpp/core_subsystems.hpp',"
content = re.sub(pattern, replacement, content)

pattern2 = r"'cpp/module/core\.hpp',"
replacement2 = r"'cpp/module/core.hpp',\n  'cpp/module/core_pillar.hpp',"
content = re.sub(pattern2, replacement2, content)


with open('bobgui/meson.build', 'w') as f:
    f.write(content)
