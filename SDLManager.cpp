#include "SDLManager.h"

SDLManager::SDLManager(){
    //init window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING)== 0) {
		cout << "Subsystems Initialized!.." << endl;
        
        
        win_height = 480;
        win_width = 640;

        curr_screen_size = SCREENSIZE::is640x480;
        last_non_fullscreen_size = SCREENSIZE::is640x480;

		this->window = SDL_CreateWindow("Blackjack", SDL_WINDOWPOS_UNDEFINED, 
                                        SDL_WINDOWPOS_UNDEFINED, win_width, win_height, SDL_WINDOW_OPENGL);

		if (this->window != nullptr) {
			cout << "Window Created" << endl;
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            this->context = SDL_GL_CreateContext(this->window);

            //load function pointers(OpenGL) for the SDL_Context
            if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
                cout << "\nGlad was not initalized!\n";
                exit(1);
            }

            // glClearColor(1.f,0.f,1.f,1.f); //background
            // glViewport(0,0, win_height, win_width);
		}
        getOpenGLInfo();
		// this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

		// if (this->renderer != nullptr) {
		// 	SDL_SetRenderDrawColor(this->renderer, 0, 255, 255, 255);
		// 	cout << "Renderer created!" << endl;
		// }
        // int w;
        // int h;
        
        // SDL_GetRendererOutputSize(renderer, &w, &h);
        // cout << "\nWidth: " << w << ", Height: " << h <<"\n";
        // //generate textures
        // background = IMG_LoadTexture(renderer, "assets/background.jpg");
        // //SDL_QueryTexture(background, NULL, NULL, &w, &h);
        // //background texture should always be up
        // SDL_Rect texture;
        // texture.w = w;
        // texture.h = h;
        // SDL_RenderCopy(renderer, background, NULL, &texture);
        // SDL_RenderPresent(renderer);
        // cout << "\nDrawing background";
        
        //drawCards();
    }
}

SDL_Event SDLManager::pollEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_WINDOWEVENT){
        resize(event.window.data1,event.window.data2);
    }
    return event;

}

void SDLManager::drawCard(card thisCard, int n){
    string suite = getCardSuite(thisCard);
    string value = getCardValuePath(thisCard);

    cout << "\nSuit: " << suite <<"\nValue: " << value;


    string path = "assets/Playing Cards/card-" + suite + "-" + value + ".png";
    //SDL_Texture *currCard = IMG_LoadTexture()
    cout << "\n" << path << "\n";
}

void SDLManager::resize(int width, int height){
    //  SDL_Surface *surface = SDL_GetWindowSurface(window);
    //  SDL_BlitSurface(background, NULL, surface, NULL);
    //  SDL_UpdateWindowSurface(window);
}

void SDLManager::update(){
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    //SDL_GL_MakeCurrent(window, context);
}



void SDLManager::getOpenGLInfo(){
    cout << "\nVERSION: " << glGetString(GL_VERSION);
    cout << "\nVENDOR: " << glGetString(GL_VENDOR);
    cout << "\nRENDERER: " << glGetString(GL_RENDERER);
}

void SDLManager::VertexSpecification(){
        const vector<GLfloat> vertexPosition {
            //x     //y   //z
            -0.8f, -0.8f, 0.0f, //vertex 1
            0.8f, -0.8f, 0.0f,  //vertex 2
            0.0f, 0.8f, 0.0f    //vertex 3
        };

        //generate vertex array and assing id to vertexArrayObject
        glGenVertexArrays(1, &vertexArrayObject);
        //bind the array
        glBindVertexArray(vertexArrayObject);

        //start generating Vertex buffer object
        glGenBuffers(1, &vertexBufferObject);
        //bind new buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        //send the data to the buffer
        glBufferData(GL_ARRAY_BUFFER,vertexPosition.size() * sizeof(GLfloat), vertexPosition.data(), GL_STATIC_DRAW);
        //enable vertex attribution array
        glEnableVertexAttribArray(0);
        //glVertexAttribPointer(GLuint index, GLint size(num of data points for each vertex), 
        //GLenum type(type of data in vector), GLboolean normalize, GLsizei stride(byte offset), *offset(the pointer for the offset))
        glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0,(void*)0);
        //close the arrays
        glBindVertexArray(0);
        //disable enables
        glDisableVertexAttribArray(0);

}

GLuint SDLManager::compileShader(GLuint type, const string& source){
        GLuint shaderObject;

        if(type == GL_VERTEX_SHADER){
            shaderObject = glCreateShader(GL_VERTEX_SHADER);
        }else if(type == GL_FRAGMENT_SHADER){
            shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
        }

        const char* temp = source.c_str();

        glShaderSource(shaderObject, 1 ,&temp,nullptr);
        glCompileShader(shaderObject);

        return shaderObject;
}

GLuint SDLManager::createShader(const string &vertexShader, const string &fragmentShader){
        GLuint programObject = glCreateProgram();

        GLuint myVertexShader = compileShader(GL_VERTEX_SHADER, vertexShader);
        GLuint myFragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        //attach compiled shaders
        glAttachShader(programObject, myVertexShader);
        glAttachShader(programObject, myFragmentShader);
        //link these two shaders
        glLinkProgram(programObject);

        //error checking
        glValidateProgram(programObject);
        //glDetachShader, glDeleteShader

        return programObject;
}

void SDLManager::createGraphicsPipeline(){\
    cout << "\nPIPELINE ID: " << graphicsPipelineShader;
    graphicsPipelineShader = createShader(vertexShaderSource,fragmentShaderSource);
    cout << "\nPIPELINE ID: " << graphicsPipelineShader;
}

void SDLManager::pDraw(){
    //clear screen
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    //assign view to opengl
    glViewport(0, 0, win_width, win_height);
    //assign draw color
    glClearColor(1.f, 1.f, 0.f, 1.f);


    //clear background color
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(graphicsPipelineShader);
}

void SDLManager::draw(){
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    //update screen
    SDL_GL_SwapWindow(window);
}


SDLManager::~SDLManager(){
    SDL_DestroyWindow(window);
    //SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
//fill card texture array
        //string tempArr[] = {"clubs", "diamonds", "hearts", "spades"};
        //load inital card
        //SDL_Texture *temp = IMG_LoadTexture(renderer, "assets/Playing Cards/card-back1.png");
        //cardTextures.push_back(temp);

        //load rest of cards
        //for(int i = 0; i < 4; i++){
            //for(int j = 1; j <= 13; j++){
            //SDL_Texture *temp2;
            //string currentText = "assets/Playing Cards/card-" + tempArr[i] + "-" + to_string(j) + ".png";
            //temp2 = IMG_LoadTexture(renderer, currentText.c_str());
            //cardTextures.push_back(temp2);
            //cout << currentText;
          //  }
            //temp = IMG_LoadTexture(renderer,currentText.c_str());
            //cardTextures->push_back(temp);
        //}