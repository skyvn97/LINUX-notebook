from subprocess import call
import os

tex_file = open("part1.tex").readlines()
for (dirpath, dirnames, filenames) in os.walk('.'):
    for x in filenames:
        if x.split('.')[-1] in ["cpp", "java"]:
            tex_file.append("\\code{%s}{%s}\n" % (x.split('.')[0], os.path.join(dirpath, x).replace('\\', '/')))
tex_file.extend(open("part2.tex").readlines())
open("build.tex", "w").write("".join(tex_file))
call(["lualatex", "build.tex"])
call(["lualatex", "build.tex"])
