FROM base/archlinux
WORKDIR /deploy
COPY . /deploy
COPY aur /root/.ssh/id_rsa
ARG VERSION

RUN pacman -Sy
RUN pacman -S --needed --noconfirm git openssh sudo
RUN chmod 600 /root/.ssh/id_rsa
RUN ssh-keyscan -t rsa aur.archlinux.org >> ~/.ssh/known_hosts
RUN useradd --no-create-home --shell=/bin/false build && usermod -L build
RUN echo "build ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
RUN echo "root ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

RUN /deploy/deploy.sh
