@Library('semantic_releasing') _

podTemplate(label: 'mypod', containers: [
        containerTemplate(name: 'docker', image: 'docker', ttyEnabled: true, command: 'cat'),
        containerTemplate(name: 'kubectl', image: 'lachlanevenson/k8s-kubectl:v1.8.0', command: 'cat', ttyEnabled: true),
        containerTemplate(name: 'curl', image: 'khinkali/jenkinstemplate:0.0.3', command: 'cat', ttyEnabled: true),
        containerTemplate(name: 'node', image: 'node', ttyEnabled: true, command: 'cat'),
        containerTemplate(name: 'npm-jdk', image: 'khinkali/npm-java:0.0.3', ttyEnabled: true, command: 'cat')
],
        volumes: [
                hostPathVolume(mountPath: '/var/run/docker.sock', hostPath: '/var/run/docker.sock'),
        ]) {
    node('mypod') {
        properties([
                buildDiscarder(
                        logRotator(artifactDaysToKeepStr: '',
                                artifactNumToKeepStr: '',
                                daysToKeepStr: '',
                                numToKeepStr: '30'
                        )
                ),
                pipelineTriggers([])
        ])

        /*
        stage('checkout') {
            git url: 'https://github.com/khinkali/cockpit'
        }

        stage('build image & git tag & docker push') {
            container('node') {
                sh 'npm install'
                sh 'npm run mlbuild'
                sh 'npm run build'
            }

            env.VERSION = semanticReleasing()
            currentBuild.displayName = env.VERSION

            sh "git config user.email \"jenkins@khinkali.ch\""

            sh "git config user.name \"Jenkins\""
            sh "git tag -a ${env.VERSION} -m \"${env.VERSION}\""
            withCredentials([usernamePassword(credentialsId: 'github', passwordVariable: 'GIT_PASSWORD', usernameVariable: 'GIT_USERNAME')]) {
                sh "git push https://${GIT_USERNAME}:${GIT_PASSWORD}@github.com/khinkali/cockpit.git --tags"
            }

            container('docker') {
                sh "docker build -t khinkali/cockpit:${env.VERSION} ."
                withCredentials([usernamePassword(credentialsId: 'dockerhub', passwordVariable: 'DOCKER_PASSWORD', usernameVariable: 'DOCKER_USERNAME')]) {
                    sh "docker login --username ${DOCKER_USERNAME} --password ${DOCKER_PASSWORD}"
                }
                sh "docker push khinkali/cockpit:${env.VERSION}"
            }
        }

        stage('deploy to test') {
            sh "sed -i -e 's/        image: khinkali\\/cockpit:0.0.1/        image: khinkali\\/cockpit:${env.VERSION}/' kubeconfig.yml"
            container('kubectl') {
                sh "kubectl apply -f kubeconfig.yml"
            }
        }
*/
        stage('UI Tests') {
            /*
            withCredentials([usernamePassword(credentialsId: 'testuser', passwordVariable: 'password', usernameVariable: 'username')]) {
                sh "sed -i -e 's/user: \"todo\"/user: \"${username}\"/' globals.js"
                sh "sed -i -e 's/password: \"todo\"/password: \"${password}\"/' globals.js"
            }
            */
            container('npm-jdk') {
                sh '''
                   npm install nightwatch -g
                   ls -la
                   nightwatch UIT --env integration
                   '''
            }
            junit allowEmptyResults: true, testResults: '**/reports/*.xml'
        }

        stage('deploy to prod') {
            input(message: 'manuel user tests ok?')
            withCredentials([usernamePassword(credentialsId: 'github-api-token', passwordVariable: 'GITHUB_TOKEN', usernameVariable: 'GIT_USERNAME')]) {
                container('curl') {
                    gitHubRelease(env.VERSION, 'khinkali', 'cockpit', GITHUB_TOKEN)
                }
            }
            sh "sed -i -e 's/  namespace: test/  namespace: default/' kubeconfig.yml"
            sh "sed -i -e 's/    nodePort: 31300/    nodePort: 30300/' kubeconfig.yml"
            container('kubectl') {
                sh "kubectl apply -f kubeconfig.yml"
            }
        }
    }
}