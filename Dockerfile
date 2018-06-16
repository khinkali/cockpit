FROM khinkali/nginx:0.0.1

WORKDIR /usr/share/nginx/html
RUN rm index.html
ADD dist/ /usr/share/nginx/html/