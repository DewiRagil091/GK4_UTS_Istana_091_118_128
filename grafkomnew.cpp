#include <glut.h>
#include <cmath>

//Variabel posisi karakter dan lompatan
float characterX = -0.98f; 
float characterY = -0.7f;   
bool isJumping = false;     
float jumpSpeed = 25.0f;    
float gravity = 0.005f;     

 // Variabel posisi awan
float cloudX1 = -0.6f;
float cloudX2 = 0.0f;
float cloudX3 = 0.6f;

// Variabel posisi batu
float brickX = 0.3f;        
float brickY = -0.7f;       
float brickWidth = 0.15f;   
float brickHeight = 0.5f;  

// Fungsi untuk menggambar lingkaran
void drawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); 
    for (int i = 0; i <= segments; i++) {
        float angle = (i * 2.0f * 3.1415926f) / segments;
        float dx = radius * cos(angle);
        float dy = radius * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Fungsi untuk menggambar pohon
void drawTree(float x, float y) {
    // Menggambar batang pohon
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.25f, 0.0f);

    // Menyesuaikan lebar dan tinggi batang
    glVertex2f(x - 0.05f, y);        
    glVertex2f(x + 0.05f, y);        
    glVertex2f(x + 0.05f, y - 0.2f); 
    glVertex2f(x - 0.05f, y - 0.2f); 
    glEnd();

    // Menggambar bagian pohon 
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.7f, 0.0f);

    // Segitiga teratas
    glVertex2f(x - 0.1f, y + 0.3f); 
    glVertex2f(x + 0.1f, y + 0.3f);
    glVertex2f(x, y + 0.5f);

    // Segitiga tengah
    glVertex2f(x - 0.15f, y + 0.15f); 
    glVertex2f(x + 0.15f, y + 0.15f);
    glVertex2f(x, y + 0.35f);

    // Segitiga terbawah
    glVertex2f(x - 0.2f, y);         
    glVertex2f(x + 0.2f, y);
    glVertex2f(x, y + 0.2f);

    glEnd();

}

// Fungsi untuk menggambar awan
void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f); 
    drawCircle(x, y, 0.08f, 50); 
    drawCircle(x + 0.1f, y, 0.1f, 50); 
    drawCircle(x + 0.2f, y, 0.08f, 50); 
}

// Fungsi untuk menggambar matahari dengan sinar
void drawSun(float x, float y, float radius) {
    glColor3f(1.0f, 0.9f, 0.0f); 
    drawCircle(x, y, radius, 50); 

    // Menggambar sinar matahari
    glColor3f(1.0f, 0.9f, 0.0f); 
    for (int i = 0; i < 8; i++) {
        float angle = i * 45.0f * 3.1415926f / 180.0f; 
        float dx = radius * 1.5f * cosf(angle); 
        float dy = radius * 1.5f * sinf(angle); 

        glBegin(GL_LINES);
        glVertex2f(x, y);            
        glVertex2f(x + dx, y + dy);     
        glEnd();
    }
}

// Fungsi untuk menggambar istana atau bangunan kerajaan
void drawCastle(float x, float y) {
    // Gambar bangunan istana (persegi panjang besar)
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.5f, 0.9f); 
    glVertex2f(x - 0.3f, y);      
    glVertex2f(x + 0.3f, y);      
    glVertex2f(x + 0.3f, y + 0.4f); 
    glVertex2f(x - 0.3f, y + 0.4f); 
    glEnd();

    // Gambar menara istana (persegi panjang tinggi)
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.0f, 0.5f); 
    glVertex2f(x - 0.1f, y + 0.4f); 
    glVertex2f(x + 0.1f, y + 0.4f); 
    glVertex2f(x + 0.1f, y + 0.7f); 
    glVertex2f(x - 0.1f, y + 0.7f); 
    glEnd();

    // Gambar atap menara (piramida)
    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.4f, 1.0f);
    glVertex2f(x - 0.15f, y + 0.7f); 
    glVertex2f(x + 0.15f, y + 0.7f); 
    glVertex2f(x, y + 0.9f);        
    glEnd();

    // Tambahkan elemen hiasan seperti jendela atau gerbang
    // Gambar jendela
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.8f, 1.0f); 
    glVertex2f(x - 0.1f, y + 0.2f);
    glVertex2f(x + 0.1f, y + 0.2f);
    glVertex2f(x + 0.1f, y + 0.3f);
    glVertex2f(x - 0.1f, y + 0.3f);
    glEnd();

    // Gambar gerbang istana (pagar kerajaan)
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.6f, 0.9f); 
    glVertex2f(x - 0.35f, y - 0.2f);
    glVertex2f(x + 0.35f, y - 0.2f); 
    glVertex2f(x + 0.35f, y);       
    glVertex2f(x - 0.35f, y);        
    glEnd();

    // Gambar tiang pagar kiri
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.4f, 0.8f); 
    glVertex2f(x - 0.4f, y - 0.2f); 
    glVertex2f(x - 0.3f, y - 0.2f); 
    glVertex2f(x - 0.3f, y + 0.3f); 
    glVertex2f(x - 0.4f, y + 0.3f); 
    glEnd();

    // Gambar tiang pagar kanan
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.4f, 0.8f); 
    glVertex2f(x + 0.4f, y - 0.2f); 
    glVertex2f(x + 0.3f, y - 0.2f); 
    glVertex2f(x + 0.3f, y + 0.3f); 
    glVertex2f(x + 0.4f, y + 0.3f); 
    glEnd();
}

// Fungsi untuk menggambar batu
void drawBrickWall(float x, float y, int rows, int columns, float brickWidth, float brickHeight) {
    glColor3f(0.5f, 0.4f, 0.2f);  
    for (int i = 0; i < rows; i++) {
        float offsetX = (i % 2 == 0) ? 0.0f : brickWidth / 2.0f;  
        for (int j = 0; j < columns; j++) {
            float brickX = x + offsetX + j * brickWidth - (columns * brickWidth) / 2.0f;
            float brickY = y - i * brickHeight;

            glBegin(GL_QUADS); 
            glVertex2f(brickX, brickY);                    
            glVertex2f(brickX + brickWidth, brickY);       
            glVertex2f(brickX + brickWidth, brickY - brickHeight);
            glVertex2f(brickX, brickY - brickHeight);      
            glEnd(); 
        }

    }
}

// Fungsi untuk menggambar karakter
void drawCharacter(float x, float y) {
    float scale = 2.0f; // Faktor skala untuk memperbesar karakter lebih besar lagi

    // Kepala
    glColor3ub(255, 220, 180); 
    glBegin(GL_QUADS);
    glVertex2f(x - 0.04f * scale, y + 0.14f * scale);
    glVertex2f(x + 0.04f * scale, y + 0.14f * scale);
    glVertex2f(x + 0.04f * scale, y + 0.2f * scale);
    glVertex2f(x - 0.04f * scale, y + 0.2f * scale);
    glEnd();

    // Rambut
    glColor3ub(100, 60, 40); 
    glBegin(GL_QUADS);
    glVertex2f(x - 0.04f * scale, y + 0.19f * scale);
    glVertex2f(x + 0.04f * scale, y + 0.19f * scale);
    glVertex2f(x + 0.04f * scale, y + 0.21f * scale);
    glVertex2f(x - 0.04f * scale, y + 0.21f * scale);
    glEnd();

    // Mata
    glColor3ub(0, 0, 0); 
    glBegin(GL_QUADS);
    glVertex2f(x - 0.018f * scale, y + 0.17f * scale);
    glVertex2f(x - 0.012f * scale, y + 0.17f * scale);
    glVertex2f(x - 0.012f * scale, y + 0.18f * scale);
    glVertex2f(x - 0.018f * scale, y + 0.18f * scale);

    glVertex2f(x + 0.012f * scale, y + 0.17f * scale);
    glVertex2f(x + 0.018f * scale, y + 0.17f * scale);
    glVertex2f(x + 0.018f * scale, y + 0.18f * scale);
    glVertex2f(x + 0.012f * scale, y + 0.18f * scale);
    glEnd();

    // Telinga
    glColor3ub(255, 220, 180); 
    glBegin(GL_QUADS);
    glVertex2f(x - 0.045f * scale, y + 0.17f * scale);
    glVertex2f(x - 0.04f * scale, y + 0.17f * scale);
    glVertex2f(x - 0.04f * scale, y + 0.19f * scale);
    glVertex2f(x - 0.045f * scale, y + 0.19f * scale);

    glVertex2f(x + 0.04f * scale, y + 0.17f * scale); 
    glVertex2f(x + 0.045f * scale, y + 0.17f * scale);
    glVertex2f(x + 0.045f * scale, y + 0.19f * scale);
    glVertex2f(x + 0.04f * scale, y + 0.19f * scale);
    glEnd();

    // Hidung
    glColor3ub(255, 200, 170); 
    glBegin(GL_QUADS);
    glVertex2f(x - 0.005f * scale, y + 0.155f * scale);
    glVertex2f(x + 0.005f * scale, y + 0.155f * scale);
    glVertex2f(x + 0.005f * scale, y + 0.16f * scale);
    glVertex2f(x - 0.005f * scale, y + 0.16f * scale);
    glEnd();

    // Mulut
    glColor3ub(255, 100, 100); 
    glBegin(GL_QUADS);
    glVertex2f(x - 0.012f * scale, y + 0.14f * scale);
    glVertex2f(x + 0.012f * scale, y + 0.14f * scale);
    glVertex2f(x + 0.012f * scale, y + 0.145f * scale);
    glVertex2f(x - 0.012f * scale, y + 0.145f * scale);
    glEnd();

    // Badan
    glColor3ub(150, 250, 15); 
    glBegin(GL_QUADS);
    glVertex2f(x - 0.05f * scale, y + 0.07f * scale);
    glVertex2f(x + 0.05f * scale, y + 0.07f * scale);
    glVertex2f(x + 0.05f * scale, y + 0.14f * scale);
    glVertex2f(x - 0.05f * scale, y + 0.14f * scale);
    glEnd();

    // Lengan
    glColor3ub(255, 220, 180);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.06f * scale, y + 0.08f * scale); 
    glVertex2f(x - 0.05f * scale, y + 0.08f * scale);
    glVertex2f(x - 0.05f * scale, y + 0.14f * scale);
    glVertex2f(x - 0.06f * scale, y + 0.14f * scale);

    glVertex2f(x + 0.05f * scale, y + 0.08f * scale); 
    glVertex2f(x + 0.06f * scale, y + 0.08f * scale);
    glVertex2f(x + 0.06f * scale, y + 0.14f * scale);
    glVertex2f(x + 0.05f * scale, y + 0.14f * scale);
    glEnd();

    // Kaki
    glColor3ub(0, 0, 255); 
    glBegin(GL_QUADS);
    glVertex2f(x - 0.025f * scale, y);
    glVertex2f(x + 0.025f * scale, y);
    glVertex2f(x + 0.025f * scale, y + 0.07f * scale);
    glVertex2f(x - 0.025f * scale, y + 0.07f * scale);
    glEnd();

    // Tapak kaki
    glColor3ub(0, 0, 0); 
    glBegin(GL_QUADS);
    glVertex2f(x - 0.025f * scale, y - 0.02f * scale); 
    glVertex2f(x, y - 0.02f * scale);
    glVertex2f(x, y);
    glVertex2f(x - 0.025f * scale, y);

    glVertex2f(x, y - 0.02f * scale); 
    glVertex2f(x + 0.025f * scale, y - 0.02f * scale);
    glVertex2f(x + 0.025f * scale, y);
    glVertex2f(x, y);
    glEnd();
}

// Fungsi menggambar peri
void drawFairy(float x, float y) {
    // Kepala
    glColor3ub(255, 220, 180);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159f / 180;
        glVertex2f(x + 0.01f * cos(theta), y + 0.01f * sin(theta));
    }
    glEnd();

    // Sayap
    glColor4ub(200, 200, 255, 150); 
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y); 
    glVertex2f(x - 0.03f, y + 0.02f);
    glVertex2f(x - 0.01f, y + 0.05f);

    glVertex2f(x, y); 
    glVertex2f(x + 0.03f, y + 0.02f);
    glVertex2f(x + 0.01f, y + 0.05f);
    glEnd();

    // Badan
    glColor3ub(255, 100, 200);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.005f, y - 0.02f);
    glVertex2f(x + 0.005f, y - 0.02f);
    glVertex2f(x + 0.005f, y);
    glVertex2f(x - 0.005f, y);
    glEnd();

    // Kaki
    glBegin(GL_LINES);
    glVertex2f(x - 0.005f, y - 0.02f); 
    glVertex2f(x - 0.008f, y - 0.04f);

    glVertex2f(x + 0.005f, y - 0.02f); 
    glVertex2f(x + 0.008f, y - 0.04f);
    glEnd();
}

// Fungsi melakukan aktivitas dengan menekan beberapa keyboard
void keyboard(unsigned char key, int x, int y) {
    if (key == 'a' || key == 'A') { 
        characterX -= 0.03f; 
    }
    if (key == 'd' || key == 'D') { 
        characterX += 0.03f; 
    }
    if ((key == 'w' || key == 'W') && !isJumping) {
        isJumping = true;
        jumpSpeed = 0.08f;  
    }
    glutPostRedisplay(); 
}

// Fungsi melakukan aktivitas dengan menekan beberapa keyboard
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
        if (!isJumping) {
            isJumping = true;
            jumpSpeed = 0.08f;
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) { 
        characterX = 0.0f;
        characterY = 0.0f;
        isJumping = false;
        jumpSpeed = 0.0f;
    }
    glutPostRedisplay();
}


void updateJump() {
    if (isJumping) {
        // Bergerak ke atas
        characterY += jumpSpeed;  
        jumpSpeed -= gravity;    

        // Cek apakah karakter sudah mencapai puncak lompatan dan mulai turun
        if (jumpSpeed <= 0.0f) {
            isJumping = false;  
        }
    }
    else {
        // Jika karakter tidak melompat, gravitasi akan menarik karakter ke bawah
        if (characterY > -0.7f) {
            characterY -= gravity;  
        }
        else {
            characterY = -0.7f;  
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Membersihkan layar dengan warna latar belakang

    // gradasi langit 
    glBegin(GL_QUADS);
    glColor3f(0.529f, 0.808f, 0.922f);
    glVertex2f(-1.0f, 1.0f); 
    glVertex2f(1.0f, 1.0f);  
    glColor3f(1.0f, 1.0f, 1.0f); 
    glVertex2f(1.0f, 0.0f);   
    glVertex2f(-1.0f, 0.0f); 
    glEnd();

    // rumput hijau
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.3f, 0.0f); 
    glVertex2f(-1.0f, -1.0f); 
    glVertex2f(1.0f, -1.0f);  
    glVertex2f(1.0f, -0.4f);  
    glVertex2f(-1.0f, -0.4f); 
    glEnd();

    //Menggambar istana atau bangunan kerajaan
    drawCastle(0.6f, -0.3f); 

    // Menambahkan 3 pohon  kecil yang berjejer dari kiri ke kanan
    drawTree(-0.8f, -0.3f); 
    drawTree(-0.4f, -0.3f);  
    drawTree(0.0f, -0.3f);  

    // Logika lompatan
    if (isJumping) {
        characterY += jumpSpeed;  
        jumpSpeed -= gravity;     
        if (characterY <= -0.7f) { 
            characterY = -0.7f;
            isJumping = false;  
        }
    }

    // Update posisi karakter berdasarkan gravitasi dan lompatan
    updateJump();

    
    // Menggambar batu bata kecil yang tersusun ke atas 
    drawBrickWall(-0.6f, -0.65f, 4, 2, 0.05f, 0.02f);
    drawBrickWall(-0.1f, -0.65f, 4, 2, 0.05f, 0.02f); 
    drawBrickWall(0.4f, -0.65f, 4, 2, 0.05f, 0.02f); 


    // Karakter
    drawCharacter(characterX, characterY);

    // Logika lompatan
    if (isJumping) {
        characterY += jumpSpeed;  
        jumpSpeed -= gravity;     
        if (characterY <= -0.7f) { 
            characterY = -0.7f;
            isJumping = false; 
        }
    }

    // Draw two fairies at different positions in the sky
    drawFairy(-0.2f, 0.5f); 
    drawFairy(0.3f, 0.6f);  
    drawFairy(-0.9f, 0.5f); 
    drawFairy(0.4f, 0.8f);  

    cloudX1 += 0.0001f; 
    cloudX2 += 0.0001f; 
    cloudX3 += 0.0001f; 

    // Jika awan keluar dari layar di sisi kanan, kembalikan ke sisi kiri
    if (cloudX1 > 1.0f) { 
        cloudX1 = -0.5f; 
    }
    if (cloudX2 > 1.0f) { 
        cloudX2 = -0.5f; 
    }
    if (cloudX3 > 1.0f) { 
        cloudX3 = -0.5f; 
    }
    // Menggambar semua awan
    drawCloud(cloudX1, 0.6f); 
    drawCloud(cloudX2, 0.8f); 
    drawCloud(cloudX3, 0.7f); 

    // Menambahkan matahari dengan sinar
    drawSun(-0.8f, 0.8f, 0.1f); 

   

    glutSwapBuffers(); 
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 

    // Mengatur mode proyeksi dan mengatur sistem koordinat 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); 
}

int main(int argc, char** argv) {
    // Inisialisasi GLUT dan pengaturan jendela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600); 
    glutCreateWindow("Kerajaan dan Pemandangan Alam");
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    init(); 

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop(); 
   

    return 0;
}