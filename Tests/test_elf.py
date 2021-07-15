import subprocess
import os


def test_elf():
    for i in range(1, 5):
        string = 'input_files/input' + str(i) + ' --info-header --info-plt --info-shstrtab ' \
                                                '--info-symtab --checksec '
        input_process = subprocess.Popen(['../koskassembler ' + string], stdout=subprocess.PIPE, shell=True)
        input_elf, err = input_process.communicate()
        input_elf = input_elf.decode()
        with open('output_files/output' + str(i), 'r') as f:
            output_elf = f.read()
        input_elf = os.linesep.join([s for s in input_elf.splitlines() if s])
        output_elf = os.linesep.join([s for s in output_elf.splitlines() if s])
        assert input_elf == output_elf


test_elf()
