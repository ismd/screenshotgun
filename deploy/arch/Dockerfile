FROM base/archlinux
WORKDIR /deploy
COPY . /deploy
ARG VERSION

RUN pacman -Sy
RUN pacman -S --needed --noconfirm base-devel git openssh

RUN useradd -m build
RUN echo "build ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

RUN chown -R build /deploy
RUN mkdir /build && chown build /build
RUN sudo VERSION=$VERSION -u build /deploy/deploy.sh
