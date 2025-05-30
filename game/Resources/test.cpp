// == ==============================================================================================
//       DESERT
// == ==============================================================================================
glClearColor(0.75f, 0.52f, 0.3f, 1.0f);
[...]
glm::vec3 pointLightColors[] = {
    glm::vec3(1.0f, 0.6f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0, 0.0),
    glm::vec3(0.2f, 0.2f, 1.0f)
};
[...]
// Directional light
shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);       
shader.setVec3("dirLight.ambient", 0.3f, 0.24f, 0.14f);  
shader.setVec3("dirLight.diffuse", 0.7f, 0.42f, 0.26f); 
shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
// Point light 1
shader.setVec3("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);     
shader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.1,  pointLightColors[0].y * 0.1,  pointLightColors[0].z * 0.1);       
shader.setVec3("pointLights[0].diffuse", pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z); 
shader.setVec3("pointLights[0].specular", pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
shader.setFloat("pointLights[0].constant", 1.0f);
shader.setFloat("pointLights[0].linear", 0.09);
shader.setFloat("pointLights[0].quadratic", 0.032);       
// Point light 2
shader.setVec3("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);     
shader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.1,  pointLightColors[1].y * 0.1,  pointLightColors[1].z * 0.1);       
shader.setVec3("pointLights[1].diffuse", pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z); 
shader.setVec3("pointLights[1].specular", pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
shader.setFloat("pointLights[1].constant", 1.0f);
shader.setFloat("pointLights[1].linear", 0.09);
shader.setFloat("pointLights[1].quadratic", 0.032);       
// Point light 3
shader.setVec3("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);     
shader.setVec3("pointLights[2].ambient", pointLightColors[2].x * 0.1,  pointLightColors[2].y * 0.1,  pointLightColors[2].z * 0.1);       
shader.setVec3("pointLights[2].diffuse", pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z); 
shader.setVec3("pointLights[2].specular" ,pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
shader.setFloat("pointLights[2].constant", 1.0f);
shader.setFloat("pointLights[2].linear", 0.09);
shader.setFloat("pointLights[2].quadratic", 0.032);       
// Point light 4
shader.setVec3("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);     
shader.setVec3("pointLights[3].ambient", pointLightColors[3].x * 0.1,  pointLightColors[3].y * 0.1,  pointLightColors[3].z * 0.1);       
shader.setVec3("pointLights[3].diffuse", pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z); 
shader.setVec3("pointLights[3].specular", pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
shader.setFloat("pointLights[3].constant", 1.0f);
shader.setFloat("pointLights[3].linear", 0.09);
shader.setFloat("pointLights[3].quadratic", 0.032);       
// SpotLight
shader.setVec3("spotLight.position", camera.Position.x, camera.Position.y, camera.Position.z);   
shader.setVec3("spotLight.direction", camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);
shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);   
shader.setVec3("spotLight.diffuse", 0.8f, 0.8f, 0.0f); 
shader.setVec3("spotLight.specular", 0.8f, 0.8f, 0.0f);
shader.setFloat("spotLight.constant", 1.0f);
shader.setFloat("spotLight.linear", 0.09);
shader.setFloat("spotLight.quadratic", 0.032);            
shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(13.0f)));  
// == ==============================================================================================
//       FACTORY
// == ==============================================================================================
glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
[...]
glm::vec3 pointLightColors[] = {
    glm::vec3(0.2f, 0.2f, 0.6f),
    glm::vec3(0.3f, 0.3f, 0.7f),
    glm::vec3(0.0f, 0.0f, 0.3f),
    glm::vec3(0.4f, 0.4f, 0.4f)
};
[...]
        // Directional light
        shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);      
        shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.1f); 
        shader.setVec3( "dirLight.diffuse", 0.2f, 0.2f, 0.7); 
        shader.setVec3( "dirLight.specular", 0.7f, 0.7f, 0.7f);
        // Point light 1
        shader.setVec3("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);        
        shader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.1,  pointLightColors[0].y * 0.1,  pointLightColors[0].z * 0.1);      
        shader.setVec3("pointLights[0].diffuse", pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z); 
        shader.setVec3("pointLights[0].specular", pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
        shader.setFloat("pointLights[0].constant", 1.0f);
        shader.setFloat("pointLights[0].linear", 0.09);
        shader.setFloat("pointLights[0].quadratic", 0.032);     
        // Point light 2
        shader.setVec3("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);        
        shader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.1,  pointLightColors[1].y * 0.1,  pointLightColors[1].z * 0.1);      
        shader.setVec3("pointLights[1].diffuse", pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z); 
        shader.setVec3("pointLights[1].specular", pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
        shader.setFloat("pointLights[1].constant", 1.0f);
        shader.setFloat("pointLights[1].linear", 0.09);
        shader.setFloat("pointLights[1].quadratic", 0.032);     
        // Point light 3
        shader.setVec3("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);        
        shader.setVec3("pointLights[2].ambient", pointLightColors[2].x * 0.1,  pointLightColors[2].y * 0.1,  pointLightColors[2].z * 0.1);      
        shader.setVec3("pointLights[2].diffuse", pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z); 
        shader.setVec3("pointLights[2].specular", pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
        shader.setFloat("pointLights[2].constant", 1.0f);
        shader.setFloat("pointLights[2].linear", 0.09);
        shader.setFloat("pointLights[2].quadratic", 0.032);     
        // Point light 4
        shader.setVec3("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);        
        shader.setVec3("pointLights[3].ambient", pointLightColors[3].x * 0.1,  pointLightColors[3].y * 0.1,  pointLightColors[3].z * 0.1);      
        shader.setVec3("pointLights[3].diffuse", pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z); 
        shader.setVec3("pointLights[3].specular", pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
        shader.setFloat("pointLights[3].constant", 1.0f);
        shader.setFloat("pointLights[3].linear", 0.09);
        shader.setFloat("pointLights[3].quadratic", 0.032);     
        // SpotLight
        shader.setVec3("spotLight.position", camera.Position.x, camera.Position.y, camera.Position.z);  
        shader.setVec3("spotLight.direction", camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);
        shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);  
        shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f); 
        shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("spotLight.constant", 1.0f);
        shader.setFloat("spotLight.linear", 0.009);
        shader.setFloat("spotLight.quadratic", 0.0032);         
        shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(10.0f)));
        shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(12.5f)));
// == ==============================================================================================
//       HORROR
// == ==============================================================================================
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
[...]
glm::vec3 pointLightColors[] = {
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.3f, 0.1f, 0.1f)
};
[...]
        // Directional light
        shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);       
        shader.setVec3("dirLight.ambient", 0.0f, 0.0f, 0.0f);    
        shader.setVec3("dirLight.diffuse", 0.05f, 0.05f, 0.05); 
        shader.setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);
        // Point light 1
        shader.setVec3("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);     
        shader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.1,  pointLightColors[0].y * 0.1,  pointLightColors[0].z * 0.1);       
        shader.setVec3("pointLights[0].diffuse", pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z); 
        shader.setVec3("pointLights[0].specular", pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
        shader.setFloat("pointLights[0].constant", 1.0f);
        shader.setFloat("pointLights[0].linear", 0.14);
        shader.setFloat("pointLights[0].quadratic", 0.07);        
        // Point light 2
        shader.setVec3("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);     
        shader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.1,  pointLightColors[1].y * 0.1,  pointLightColors[1].z * 0.1);       
        shader.setVec3("pointLights[1].diffuse", pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z); 
        shader.setVec3("pointLights[1].specular", pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
        shader.setFloat("pointLights[1].constant", 1.0f);
        shader.setFloat("pointLights[1].linear", 0.14);
        shader.setFloat("pointLights[1].quadratic", 0.07);        
        // Point light 3
        shader.setVec3("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);     
        shader.setVec3("pointLights[2].ambient", pointLightColors[2].x * 0.1,  pointLightColors[2].y * 0.1,  pointLightColors[2].z * 0.1);       
        shader.setVec3("pointLights[2].diffuse", pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z); 
        shader.setVec3("pointLights[2].specular" ,pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
        shader.setFloat("pointLights[2].constant", 1.0f);
        shader.setFloat("pointLights[2].linear", 0.22);
        shader.setFloat("pointLights[2].quadratic", 0.20);        
        // Point light 4
        shader.setVec3("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);     
        shader.setVec3("pointLights[3].ambient", pointLightColors[3].x * 0.1,  pointLightColors[3].y * 0.1,  pointLightColors[3].z * 0.1);       
        shader.setVec3("pointLights[3].diffuse", pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z); 
        shader.setVec3("pointLights[3].specular", pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
        shader.setFloat("pointLights[3].constant", 1.0f);
        shader.setFloat("pointLights[3].linear", 0.14);
        shader.setFloat("pointLights[3].quadratic", 0.07);        
        // SpotLight
        shader.setVec3("spotLight.position", camera.Position.x, camera.Position.y, camera.Position.z);   
        shader.setVec3("spotLight.direction", camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);
        shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);   
        shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f); 
        shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("spotLight.constant", 1.0f);
        shader.setFloat("spotLight.linear", 0.09);
        shader.setFloat("spotLight.quadratic", 0.032);            
        shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(10.0f)));
        shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
// == ==============================================================================================
//       BIOCHEMICAL LAB
// == ==============================================================================================
glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
[...]
glm::vec3 pointLightColors[] = {
    glm::vec3(0.4f, 0.7f, 0.1f),
    glm::vec3(0.4f, 0.7f, 0.1f),
    glm::vec3(0.4f, 0.7f, 0.1f),
    glm::vec3(0.4f, 0.7f, 0.1f)
};
[...]
// Directional light
shader.setVec3("dirLight.direction"), -0.2f, -1.0f, -0.3f;       
shader.setVec3("dirLight.ambient"), 0.5f, 0.5f, 0.5f;    
shader.setVec3("dirLight.diffuse"), 1.0f, 1.0f, 1.0f; 
shader.setVec3("dirLight.specular"), 1.0f, 1.0f, 1.0f;
// Point light 1
shader.setVec3("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);     
shader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.1,  pointLightColors[0].y * 0.1,  pointLightColors[0].z * 0.1);       
shader.setVec3("pointLights[0].diffuse", pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z); 
shader.setVec3("pointLights[0].specular", pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
shader.setFloat("pointLights[0].constant", 1.0f);
shader.setFloat("pointLights[0].linear", 0.07);
shader.setFloat("pointLights[0].quadratic", 0.017);       
// Point light 2
shader.setVec3("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);     
shader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.1,  pointLightColors[1].y * 0.1,  pointLightColors[1].z * 0.1);       
shader.setVec3("pointLights[1].diffuse", pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z); 
shader.setVec3("pointLights[1].specular", pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
shader.setFloat("pointLights[1].constant", 1.0f);
shader.setFloat("pointLights[1].linear", 0.07);
shader.setFloat("pointLights[1].quadratic", 0.017);       
// Point light 3
shader.setVec3("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);     
shader.setVec3("pointLights[2].ambient", pointLightColors[2].x * 0.1,  pointLightColors[2].y * 0.1,  pointLightColors[2].z * 0.1);       
shader.setVec3("pointLights[2].diffuse", pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z); 
shader.setVec3("pointLights[2].specular" ,pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
shader.setFloat("pointLights[2].constant", 1.0f);
shader.setFloat("pointLights[2].linear", 0.07);
shader.setFloat("pointLights[2].quadratic", 0.017);       
// Point light 4
shader.setVec3("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);     
shader.setVec3("pointLights[3].ambient", pointLightColors[3].x * 0.1,  pointLightColors[3].y * 0.1,  pointLightColors[3].z * 0.1);       
shader.setVec3("pointLights[3].diffuse", pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z); 
shader.setVec3("pointLights[3].specular", pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
shader.setFloat("pointLights[3].constant", 1.0f);
shader.setFloat("pointLights[3].linear", 0.07);
shader.setFloat("pointLights[3].quadratic", 0.017);       
// SpotLight
shader.setVec3("spotLight.position", camera.Position.x, camera.Position.y, camera.Position.z);   
shader.setVec3("spotLight.direction", camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);
shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);   
shader.setVec3("spotLight.diffuse", 0.0f, 1.0f, 0.0f); 
shader.setVec3("spotLight.specular", 0.0f, 1.0f, 0.0f);
shader.setFloat("spotLight.constant", 1.0f);
shader.setFloat("spotLight.linear", 0.07);
shader.setFloat("spotLight.quadratic", 0.017);    
shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(7.0f)));
shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(10.0f)));  