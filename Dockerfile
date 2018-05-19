FROM nginx:1.12.2

WORKDIR /usr/share/nginx/html
RUN rm index.html
ADD dist/ /usr/share/nginx/html/