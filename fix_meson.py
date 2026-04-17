import re

with open('bobgui/meson.build', 'r') as f:
    content = f.read()

pattern = r"'cpp/layout\.hpp',"
replacement = r"'cpp/layout.hpp',\n  'cpp/media.hpp',"
content = re.sub(pattern, replacement, content)

with open('bobgui/meson.build', 'w') as f:
    f.write(content)
