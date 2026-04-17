import re

with open('bobgui/meson.build', 'r') as f:
    content = f.read()

pattern = r"'cpp/visual_pillar\.hpp',"
replacement = r"'cpp/visual_pillar.hpp',\n  'cpp/visual.hpp',"
content = re.sub(pattern, replacement, content)

with open('bobgui/meson.build', 'w') as f:
    f.write(content)
