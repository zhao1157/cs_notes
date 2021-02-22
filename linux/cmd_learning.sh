#======= 78 =======
# go back the previous commit 
# keep the changes
git reset --soft HEAD~1
# not keep the changes
git reset --hard HEAD~1

#======= 77 ======
docker start -ai container_name # it takes you straight to where you left last time, exiting this session will closing all other sessions
docker exec -it container_name /bin/bash # it's just like opening another session of this container, closing the session does not affect other sessions

#======== 76 ======
# set the PID namespace
docker run -it --rm --pid=host nvcr.io/nvidia/tensorflow:20.12-tf1-py3 # can see processes on the host
docker run -it --rm --pid=container:train_bert_2 nvcr.io/nvidia/tensorflow:20.12-tf1-py3 # can see the processes in container train_bert_2
#======= 75 =======
a=2 ./b.sh # in b.sh a will be 2 # no ; 
#====== 74 =======
# to exclude some files/directories from .gitignore, just like .dockerignore
*.sh # all .sh files
!create_datasets_from_start.sh # now this script will be tracked by git

#======== 73 =======
# split strings into substrings
a="xx_yy_zz"
IFS="_" # an internal variable that how bash recognizes word boundaries
read -a arr <<< "$a" # split and read the substrings into an array arr
echo ${arr[0]} ${arr[1]} ${arr[2]} # access the substrings

IFS=" " # reset the delimiter back to avoid unnecessary complexity


#======== 72 =======
# list all processes for all users
ps axu
#===== 71 =====
# install from a requirement file
pip install -r requirement.txt # cat requirement -> pynvml
#==== 70 ====
# find the number of sub-directories in a directory
ls -l dir | grep -c ^d # number of directories
=======
#====== 70 ======
a=xx.tar
b=${a%.*} # remove anything from .
echo $b # xx
#===== 69 =====
# comment in github readme.md
<!--comment goes here; can cross multiple lines-->
#===== 68 =====
# download a single file from github
# get the url of the raw file in github, that, the url after clicking on the raw button on that page
wget <raw_file_url>
#========== 67 =========
# monitor /gpu:2 
nvidia-smi dmon -s pucvmet -i 2 
#====== 66 ==========
# show only a few process in top
top -p 1234,2344,9999
#========= 65 =========
# .dockerignore
# in all directories
**/__pychche__
# in all directories and anyfile with suffix .pyc
**/*.pyc
# including README*.md files in the docker root context directory
*.md
!README*.md 
# exclude Dockerfile and .dockerignore
Dockerfile
*.dockerignore
# we might not want to include .git files
**/.git

#====== 64 ======
# mount the source dir to the dir in the container
docker run -v local_dir:dir_in_container
#======= 63 ======
#To override the ENTRYPOINT in docker image
docker run --entrypoint /bin/bash docker_image_id
#====== 62 ======
# see the output of an active container
docker logs <container_id/container_name>
#===== 61 =====
# only get the top commit in git history
git clone --depth=1 ****.git
#===== 60 =====
# Dockerfile
ARG x=X # here x is not accessible beyond FROM
FROM nvcr.io/nvidia/tensorflow:20.11-tf1-py3
RUN rm -rf /workspace/* # remove the contents in /workspace in the original image
RUN echo "love" > /workspace/README.md
COPY specml /workspace/specml # specml has to be in the Dockerfile directory
#WORKDIR is a Dockerfile command, not an environment variable
WORKDIR /workspace/specml/runner # the directory where you will be upon the container is launched
# $WORKDIR is not an environment variable in the container, we have to set it
ENV WORKDIR="/workspace/specml/runner"
#ENV VERSION=1.0 # in the docker container, ${VERSION} will just show 1.0, it will create a new layer, so even we unset it later, it still contains it
RUN export VERSION=1.0 && echo install VERSION-dependent packages && unset VERSION && echo VERSION is no longer in the environment
ADD xx.tar xxx.tar /workspace/yy/ # xx.tar will be extracted as /workspace/yy/xx, and xxx.tar as /workspace/yy/xxx
#CMD ./run_resnet50.sh # once launched a container, it will automatically run this script
#CMD ["sh", "-c", "echo; echo; echo; echo TRAINING DEMO; echo; echo; echo; sh"] # print out some lines and a text followed by some lines again, and a shell prompt in the interactive mode
#CMD ["SOME_ECHO_STRINGS"] # this is the defualt value that's gonna be echoed
#ENTRYPOINT ["echo"] # every container will start with this command
ENTRYPOINT ["sh", "-c"]
CMD ["echo this line && echo $PWD"]
ARG a=A # a is accessible when building the image, but not inside the container; ENV works in both the image and the container
RUN echo $a

#====== 59 =======
# build a docker image using Dockfile
# create a directory where to Dockerfile and other source files needed to be copied to the image
# outside of the directory
docker build -t specml_demo:latest the_directory_name
#========= 58 =========
#change the name of a network interface in linux
ifconfig peth0 down
ip link set peth0 name eth0
ifconfig eth0 up

#========== 57 ==========
# set working directory
docker run -w /home/zhaolianshui/xxx
#=========== 56 ==========
# find out network interface status
netstat -an | grep 2234
#========== 55 ==========
#save a container to an image
docker commit -m "some comment about this update" -a "author name who made such commit/update" ${container_id_or_name} ${new_name:tag}
#========== 54 ========
# if script color is lost after deleting .swp file
:set filetype=python # if it is a python script
:set filetype=cpp # if it is a cpp file
#===== 53 =====
# instructions to install docker on windows
#1. open Windows Features, uncheck four boxes (Containers, Hyper-V, Virtual Machine Platform and Windows Hypervisor Platform), then you are prompted to restart your computer, just do it.
#2. after rebooting, recheck those four boxes, and restart as prompted
#3. install docker .exe file and uncheck the WSL2 box, and install it
#4. on the docker settings console, uncheck the WSL2 box and apply the changes
#5. check the docker installation: open a terminal, check the output of the command "docker version"
#==== 52 ===
#on mac find out the number of logical cpus
sysctl -n hw.ncpu

#====== 51 =======
# make vim indent with 4 spaces
# in ~/.vimrc, add the following 3 lines
set tabstop=4
set shiftwidth=4
set expandtab
# make auto indent
filetype indent on
# make vim start where left off last time
autocmd BufWinLeave *.* mkview
autocmd BufWinEnter *.* silent loadview

#======== 50 =========
kill -9 2324 # to forcefully kill this process
kill -SIGKILL 2324 # -SIGTERM

#======== 49 =========
kill $(ps | grep iotop | cut -f 2 -d " ") # cut -f (filed) -d (delimiter)

#======== 48 ========
# not including some words
df | grep -v overlay # not including lines which have overly in them

#======= 47 =======
#in top command, use the following can be more informative
press 1: all logical cpus
press 2: cpu nodes
press c: full command line
press -n : number of lines that can be shown
press -k ： kill a process
press z: change the color of the output

#========= 46 ==========
# delete all exited docker containers
docker rm $(docker ps -q -f status=exited)

#======= 45 =======
# fail to connect to archive.ubuntu.com whne using apt-get install
#edit /etc/gai.conf line 54: uncomment

#========= 44 =======
# find all files containing a string
grep -rn horovod_mpi_built  #-r: recursive; -n: line number

#======== 43 =======
#when profiling tensorflow in horovod container, there are some complaints about libcupti not found
#the following solved this problem
LD_LIBRARY_PATH="/usr/local/cuda/compat/lib.real:/usr/local/cuda/extras/CUPTI/lib64:/usr/local/cuda/compat/lib:/usr/local/nvidia/lib:/usr/local/nvidia/lib64"

#========= 42 =======
# find out the location where a process is submitted
ls -l /proc/12356/cwd # 12356 is the process id of interest

#========== 41 ========
CUDA_VISIBLE_DEVICES='7' ./zls_run.sh

#========= 40 ========
# practice __name__ of different files
text = """print('In the imported file:', __name__)"""
with open('xx.py', 'w') as f:
        f.write(text)
import xx
print ('In the main file:', __name__)

#========= 39 =======
a="echo love you"
#run echo love you
eval $a

#=========== 38 ==========
# define a function
function f() {
        aa="love you" #global variable

        local bb="I" #only exist in function
}

f
echo aa=$aa #"love you"
echo bb=$bb # EMPTY

#======== 37 =======
#MIMD example
# --map-by ppr:1:socket:pe=2 will be overwritten by the last one, so we can not configure
# it differently
mpirun --allow-run-as-root --report-bindings -H localhost:1 -np 1 \
--map-by ppr:1:socket:pe=2 python a.py : -H localhost:3 -np 2 python b.py 1

#========== 36 =========
# to terminate a hanging process
jobs # get the job index of interest
kill %1

#========== 35 ========
# to get profile option in tensorboard
pip install -U tensorboard_plugin_profile

#========== 34 =========
# change the highlight color in vim
hi Search cterm=NONE ctermfg=black ctermbg=yellow
#========== 33 ========
# practice cut
echo "i LOVE YOU" | cut -d" " -f2 #returns LOVE
#========= 32 =========
# directly type python code in command line and execute
python -c '
import tensorflow as tf
print (tf.__version__)
for i in range(3):
  print (i)
'

#======= 31 ======
git rm removed_file.txt
#========= 30 ========
#download foler "https://github.com/NVIDIA/DeepLearningExamples/tree/master/TensorFlow/LanguageModeling/BERT/data"
# replace tree/master with trunk
svn checkout https://github.com/NVIDIA/DeepLearningExamples/trunk/TensorFlow/LanguageModeling/BERT/data

#========= 29 =========
# in vi editor, set/unset highlight searching results
:set hlsearch
:set nohlsearch
#======== 28 =======
....
#======== 27 =======
# relate the local repo to the main repo
git remote add upstream ssh://git@10.166.15.223:6222/luoxinyu/specml.git
# set the upstream un-pushable
git remote set-url --push upstream no_push
# create new branch where to make the changes
git checkout -b fix-1
#========= 26 =======
python a.py |& grep -v "sth that's not gonna show"

#========= 25 =========
# Save before/after snapshots of optimized graphs
export TF_AUTO_MIXED_PRECISION_GRAPH_REWRITE_LOG_PATH="amp_graph"
# Enable VERY verbose logging of all decisions made by AMP optimizer
export TF_CPP_VMODULE="auto_mixed_precision=2"

#======== 24 ======
bash a.sh |& tee -a output.log # append to log, not overwrite it
python b.py 2>&1 | tee -a output.log

# ====== 23 =======
#a can take values from command line or take the default value
a=${1:-"love"}

#======== 22 ======
printf -v a "2 3"
echo $a
printf -v b "%e %e %s" 7.5e-4 0.002 love # space in the format to separate
echo $b
#======= 21 =========
# enable log of auto mixed precision graph rewriter
export TF_AUTO_MIXED_PRECISION_GRAPH_REWRITE_LOG_PATH='amp_graph'

#======== 20 ========
nvidia-docker run --net=host #use the host network stack inside the container

#========= 19 =======
# not working by pip install dllogger
pip install git+https://github.com/NVIDIA/dllogger.git

#======= 18 =====
# set default value if no external values provided
echo ${1:-"default_1"} ${2:-"default_2"}

#======= 17 ========
# change image name
docker tag old_image_name new_image_name

# ======== 16 ======
more test.txt # view the content page by page by hitting the space key
less test.txt # forward and backward continuous view

#======== 15 =======
# generate ssh key
ssh-keygen
# git learning
git config --list #return the config information
#you can also modify the .gitconfig file to set up user name and email address
git config --global --add user.name "Seth" # add a new name to user.name
git config --global --replace-all user.name "Lianshui Zhao" # replace all user.name to just one entry
git config --global user.email "zhao.1157@osu.edu" #set email address
git log # see the commits histor
git status # see the changes made in the working directory copared with git commits
git add . # stage the changes
git commit -m 'message about this commit' # commit the changes in the staging area
git push # push the changes to the github repository
git checkout 'a previous version sha code' # go to a previous version
git push orgion HEAD:master --force # went to a hisotry veriosn, commit and force push to repo
git checkout master
git checkout . # revert changes made to your working copy
git rm -r --cached . # (pay attention to the dot ".") stop tracking all files
git rm --cached a.txt # stop tracking a.txt
git commit --amend # add more changes to the last commit and have a chance to modify the commit message
git commit --amend --no-edit # not change the commit message
git commit --amend -m "modified commit message" # not make any changes to the last commit, just modify the commit messages
git push -f # to push a modified commit



#========= 14 ========
# tf profiler in tensorboard (tf>=2.2)
pip install -U tensorboard_plugin_profile

# ========= 13 ========
# commands of nvprof
nvprof --query-events # return the events
nvprof --query-metrics # return the metrics(important)
nvprof --replay-mode disabled/kernel/application # some metrics/events need to replay the kernel/application, but some not(disabled)
nvprof --timeout 2 # the application will terminate in 2 seconds after the cuda driver is called
nvprof --log-file nv.outputs # redirect nvprof outputs to a log file

#========= 12 =======
# the environment variable can se set through export
export CUDA_VISIBLE_DEVICES='0'

#======== 11 ==========
# cupti error when using tf profile, --privileged solved this issue, i.e. root access; -p 8023:6006 --> outside_port:inside_port
nvidia-docker run -p 8023:6006 --shm-size=1g --ulimit memlock=-1 --ulimit stack=67108864 -it --rm --name=tf_nv_profile
 --cap-add=SYS_PTRACE  --privileged -v /home/zhaolianshui:/home/zhaolianshui nvcr.io/nvidia/tensorflow:19.10-py3

# ========= 10 ======
# convert the current time into seconds
date +%s
time_seconds=`date +%s` # `` means the return value of the command line inside, or use $(date +%s)

# ======== 9 =========
# -s means the file has non-zero size
[[ -s "$HOME/.gvm/scripts/gvm" ]] && source "$HOME/.gvm/scripts/gvm"

#========== 8 ========
# add path to environment

#========= 7 ==========
# remove all stopped containers
docker container prune
#========== 6 =========
docker images -a
docker rmi image_1 image_2
docker system prune -a

#======== 5 ========
# save and load image
docker save -o tf_20.03-tf1-py3 nvcr.io/nvidia/tensorflow:20.03-tf1-py3
docker load -i tf_20.03-tf1-py3

#=========== 4 ===========
# solve nvidia images authentication required issus
docker login nvcr.io -u '$oauthtoken' -p aXJnY2ZhcjlkaWRxY2hqYWcyNW1uZ21tcDQ6NDlmYmM0OGMtNDlhOS00ODJiLWFhMTItYjRhMDQzMThjYWYx

#======== 3 =======
useradd -m -p zhaolianshui -s /bin/bash zhaolianshui

#========= 2 =======
#find the total number of counts of a word in a file
grep -o ApplyAdam out_1 | wc -l #-o outputs each occurrence on each line
cat out_1 | grep ApplyAdam | wc -l

#=========== 1 ============
#scp
scp -r local_file zhaolianshui@10.166.5.27:/home/zhaolianshui #:/address is required
# rename a docker container
docker rename old_name new_name
# for docker images
docker tag old_name new_name
