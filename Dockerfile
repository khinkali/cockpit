FROM nginx:1.12.2

WORKDIR /usr/share/nginx/html
RUN rm index.html
ADD build/ /usr/share/nginx/html/