#!/usr/bin/env python3
import os, sys, fnmatch
from subprocess import Popen
from datetime import datetime


folderIgnore={"NULL", "examples"}

IgnoreNames={"main-si.c"}

ignorePatternFront = ["."]
onlyTakePatternEnd = [".c"]

CC="gcc"
ERRFLAGS = ["-Wall"]
CFLAGS=["-std=c99", "-ffunction-sections", "-fdata-sections", "-fopenmp", "-Os"] + ERRFLAGS
LDFLAGS=["-lm", "-Wl,-rpath", "-Wl,/usr/local/lib", "-I/usr/local/include","-fopenmp"]
OUTEXE="build/test"


gSource = "./"
gCleanEnabled = 0
gTestEnabled = 1
gTestCommands = [""]

#-----G-END-----#


TREE_SYNTX = {'E':'├', 'C':'│', 'S':'─', 'N':'└'}

def run(commands):
    Popen(commands).wait()


def log(msg):
    print(msg, end='')


def checkIfNameFound(name, nArray):
    for i in nArray:
        if fnmatch.fnmatch(name, "*"+i):
            return 1
    return 0

def compile(cfiles):

    cf = cfiles.split(" ")

    run_command = [ CC ] + CFLAGS + LDFLAGS

    for i in cf:
        run_command.append(i)
    run_command.append('-o')
    run_command.append(OUTEXE)
    
    run([ "rm","-rf","build" ])
    run(["mkdir", "build"])    
    run(run_command)



def getallFiles(dirName):
    log("Getting C files...")
    listOfFiles = list()
    for (dirpath, dirnames, filenames) in os.walk(dirName):
        dirnames[:] = [d for d in dirnames if d not in folderIgnore]
        listOfFiles += [os.path.join(dirpath, file) for file in filenames]


    log("DONE\n\n")

    return listOfFiles

def drawTree(outstr):
    lso = outstr.split(" ")
    prev = ""
    for i in lso:
        sin = i.split("/")
        
        try:
            now = sin[-2]
            if prev == now:
                log('\t')
            prev = sin[-2]
        except:
            pass

        log("\n\t\tGot: " + sin[-1])
        

def filterListintoFile(ls):

    log("Filtering Files...")
    outstr = ""
    prev = ""
    for elem in ls:
        if elem[2] != ".":
            if elem[-1] == "c":
                if checkIfNameFound(elem, IgnoreNames) != 1:
                    outstr += elem + " "
                    log("\n\t\tGot: " + elem)

    #drawTree(outstr)

    log("\nCOMPLETED\n\n")
    return outstr

def do_clean():
        log("Cleaning...\r")
        run(["rm", "-rf", "build"])
        log("COMPLETED\n")


def checkforfileExistance(source):
    try:
        fp = open(source, "rb")
        fp.close()
        return True
    except:
        return False
    

def main(source, clean, TestEnabled, testCommands):
    if clean:
        do_clean()
        return

    log("Running At ... " + source + "\n")
    # Get the list of all files in directory tree at given path
    outstr = filterListintoFile(getallFiles(source))

    log("Compiling...")



    compile(outstr[0:-1])
    if checkforfileExistance(OUTEXE):
        log("SUCCESS\n\n")
    else:
        log("FAILED\n\n")

    log("Executable: " + OUTEXE + "\n\n")


    if TestEnabled:
        log("Testing...\n")
        try:
            run([ "./"+OUTEXE] + testCommands)
            log("\nSUCCESS\n")
        except:
            log("FAILED\n")
            return
    


def argp(arg):

    global gSource, gCleanEnabled, gTestCommands, gTestEnabled

    count = 1
    for i in arg:
        if i[0] == '-':
            if i[1:] == "-clean" or i[1:] == 'c':
                gCleanEnabled= 1
            elif i[1:] == "-build" or i[1:] == 'b':
                gSource = arg[count+1]
            elif i[1:] == "-testdisable" or i[1:] == 't':
                gTestEnabled = 0
            elif i[1:] == "-testCommands" or i[1:] == 'm':
                gTestCommands = arg[count+1::]
                main(gSource, gCleanEnabled, gTestEnabled ,gTestCommands)
                return
            else:
                pass
    count += 1

    main(gSource, gCleanEnabled, gTestEnabled ,gTestCommands)
    return


if __name__ == '__main__':

    now = datetime.now()

    timestamp = datetime.timestamp(now)

    log("Starting...\n\n")
    argp(sys.argv)
    log("\nEND\n")
    
    timest1 = datetime.timestamp(datetime.now())
    print("Time Elasped...{:.3} total".format(timest1 - timestamp) )
