#include <glut.h>
#include <cmath>

float characterX = -0.98f; // Posisi X karakter
float characterY = -0.7f;   // Posisi Y karakter awal
bool isJumping = false;     // Status lompat
float jumpSpeed = 16.0f;    // Kecepatan awal saat melompat
float gravity = 0.005f;     // Gravitasi

float cloudX1 = -0.6f;
float cloudX2 = 0.0f;
float cloudX3 = 0.6f;

// Variabel posisi batu
float brickX = 0.3f;        // Posisi X batu (rintangan)
float brickY = -0.7f;       // Posisi Y batu
float brickWidth = 0.15f;   // Lebar tumpukan batu
float brickHeight = 0.5f;  // Tinggi tumpukan batu

// Fungsi untuk menggambar lingkaran
void drawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Titik tengah lingkaran
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
    // Menggambar batang pohon (persegi panjang coklat)
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.25f, 0.0f);
    glVertex2f(x - 0.02f, y); 
    glVertex2f(x + 0.02f, y);
    glVertex2f(x + 0.02f, y - 0.1f);
    glVertex2f(x - 0.02f, y - 0.1f); 
    glEnd();

    // Menggambar bagian pohon (segitiga hijau)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.7f, 0.0f);
    glVertex2f(x - 0.1f, y + 0.1f); 
    glVertex2f(x + 0.1f, y + 0.1f); 
    glVertex2f(x, y + 0.3f);

    glVertex2f(x - 0.15f, y + 0.05f); 
    glVertex2f(x + 0.15f, y + 0.05f); 
    glVertex2f(x, y + 0.2f);
    glVertex2f(x - 0.2f, y); 
    glVertex2f(x + 0.2f, y);
    glVertex2f(x, y + 0.1f); 
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



void drawBrickWall(float x, float y, int rows, int columns, float brickWidth, float brickHeight) {
    glColor3f(0.5f, 0.4f, 0.2f);  // Warna bata
    for (int i = 0; i < rows; i++) {
        float offsetX = (i % 2 == 0) ? 0.0f : brickWidth / 2.0f;  // Offset setiap baris
        for (int j = 0; j < columns; j++) {
            float brickX = x + offsetX + j * brickWidth - (columns * brickWidth) / 2.0f;
            float brickY = y - i * brickHeight;

            glBegin(GL_QUADS);  // Mulai menggambar bata
            glVertex2f(brickX, brickY);                    // Kiri atas
            glVertex2f(brickX + brickWidth, brickY);       // Kanan atas
            glVertex2f(brickX + brickWidth, brickY - brickHeight); // Kanan bawah
            glVertex2f(brickX, brickY - brickHeight);      // Kiri bawah
            glEnd();  // Selesai menggambar bata
        }

    }
}




void drawCharacter(float x, float y) {
    // Draw head
    glColor3ub(255, 220, 180); // Skin color
    glBegin(GL_QUADS);
    glVertex2f(x - 0.04f, y + 0.14f);
    glVertex2f(x + 0.04f, y + 0.14f);
    glVertex2f(x + 0.04f, y + 0.2f);
    glVertex2f(x - 0.04f, y + 0.2f);
    glEnd();

    // Draw hair
    glColor3ub(100, 60, 40); // Brown hair
    glBegin(GL_QUADS);
    glVertex2f(x - 0.04f, y + 0.19f);
    glVertex2f(x + 0.04f, y + 0.19f);
    glVertex2f(x + 0.04f, y + 0.21f);
    glVertex2f(x - 0.04f, y + 0.21f);
    glEnd();

    // Draw eyes
    glColor3ub(0, 0, 0);// Black eyes
    glBegin(GL_QUADS);
    glVertex2f(x - 0.018f, y + 0.17f);
    glVertex2f(x - 0.012f, y + 0.17f);
    glVertex2f(x - 0.012f, y + 0.18f);
    glVertex2f(x - 0.018f, y + 0.18f);

    glVertex2f(x + 0.012f, y + 0.17f);
    glVertex2f(x + 0.018f, y + 0.17f);
    glVertex2f(x + 0.018f, y + 0.18f);
    glVertex2f(x + 0.012f, y + 0.18f);
    glEnd();

    // Draw ears
    glColor3ub(255, 220, 180); // Skin color for ears
    glBegin(GL_QUADS);
    glVertex2f(x - 0.045f, y + 0.17f); // Left ear
    glVertex2f(x - 0.04f, y + 0.17f);
    glVertex2f(x - 0.04f, y + 0.19f);
    glVertex2f(x - 0.045f, y + 0.19f);

    glVertex2f(x + 0.04f, y + 0.17f); // Right ear
    glVertex2f(x + 0.045f, y + 0.17f);
    glVertex2f(x + 0.045f, y + 0.19f);
    glVertex2f(x + 0.04f, y + 0.19f);
    glEnd();

    // Draw nose
    glColor3ub(255, 200, 170); // Nose color slightly darker than skin
    glBegin(GL_QUADS);
    glVertex2f(x - 0.005f, y + 0.155f);
    glVertex2f(x + 0.005f, y + 0.155f);
    glVertex2f(x + 0.005f, y + 0.16f);
    glVertex2f(x - 0.005f, y + 0.16f);
    glEnd();

    // Draw mouth
    glColor3ub(255, 100, 100); // Red for mouth
    glBegin(GL_QUADS);
    glVertex2f(x - 0.012f, y + 0.14f);
    glVertex2f(x + 0.012f, y + 0.14f);
    glVertex2f(x + 0.012f, y + 0.145f);
    glVertex2f(x - 0.012f, y + 0.145f);
    glEnd();

    // Draw body
    glColor3ub(150, 250, 15); // Red shirt
    glBegin(GL_QUADS);
    glVertex2f(x - 0.05f, y + 0.07f);
    glVertex2f(x + 0.05f, y + 0.07f);
    glVertex2f(x + 0.05f, y + 0.14f);
    glVertex2f(x - 0.05f, y + 0.14f);
    glEnd();

    // Draw arms
    glColor3ub(255, 220, 180); // Skin color for arms
    glBegin(GL_QUADS);
    glVertex2f(x - 0.06f, y + 0.08f); // Left arm
    glVertex2f(x - 0.05f, y + 0.08f);
    glVertex2f(x - 0.05f, y + 0.14f);
    glVertex2f(x - 0.06f, y + 0.14f);

    glVertex2f(x + 0.05f, y + 0.08f); // Right arm
    glVertex2f(x + 0.06f, y + 0.08f);
    glVertex2f(x + 0.06f, y + 0.14f);
    glVertex2f(x + 0.05f, y + 0.14f);
    glEnd();

    // Draw legs
    glColor3ub(0, 0, 255); // Blue pants
    glBegin(GL_QUADS);
    glVertex2f(x - 0.025f, y);
    glVertex2f(x + 0.025f, y);
    glVertex2f(x + 0.025f, y + 0.07f);
    glVertex2f(x - 0.025f, y + 0.07f);
    glEnd();

    // Draw feet
    glColor3ub(0, 0, 0); // Black shoes
    glBegin(GL_QUADS);
    glVertex2f(x - 0.025f, y - 0.02f); // Left shoe
    glVertex2f(x, y - 0.02f);
    glVertex2f(x, y);
    glVertex2f(x - 0.025f, y);

    glVertex2f(x, y - 0.02f); // Right shoe
    glVertex2f(x + 0.025f, y - 0.02f);
    glVertex2f(x + 0.025f, y);
    glVertex2f(x, y);
    glEnd();
}

void drawFairy(float x, float y) {
    // Draw head
    glColor3ub(255, 220, 180); // Skin color
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159f / 180;
        glVertex2f(x + 0.01f * cos(theta), y + 0.01f * sin(theta));
    }
    glEnd();

    // Draw wings
    glColor4ub(200, 200, 255, 150); // Light blue with transparency
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y); // Left wing
    glVertex2f(x - 0.03f, y + 0.02f);
    glVertex2f(x - 0.01f, y + 0.05f);

    glVertex2f(x, y); // Right wing
    glVertex2f(x + 0.03f, y + 0.02f);
    glVertex2f(x + 0.01f, y + 0.05f);
    glEnd();

    // Draw body
    glColor3ub(255, 100, 200); // Pink color for body
    glBegin(GL_QUADS);
    glVertex2f(x - 0.005f, y - 0.02f);
    glVertex2f(x + 0.005f, y - 0.02f);
    glVertex2f(x + 0.005f, y);
    glVertex2f(x - 0.005f, y);
    glEnd();

    // Draw legs
    glBegin(GL_LINES);
    glVertex2f(x - 0.005f, y - 0.02f); // Left leg
    glVertex2f(x - 0.008f, y - 0.04f);

    glVertex2f(x + 0.005f, y - 0.02f); // Right leg
    glVertex2f(x + 0.008f, y - 0.04f);
    glEnd();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a' || key == 'A') { // Tombol A atau a untuk bergerak ke kiri
        characterX -= 0.03f; // Mengurangi posisi X
    }
    if (key == 'd' || key == 'D') { // Tombol D atau d untuk bergerak ke kanan
        characterX += 0.03f; // Menambah posisi X
    }
    if ((key == 'w' || key == 'W') && !isJumping) {
        isJumping = true;
        jumpSpeed = 0.08f;  // Kecepatan lompatan yang lebih lambat
    }
    glutPostRedisplay(); // Memperbarui tampilan
}

void updateJump() {
    if (isJumping) {
        // Bergerak ke atas
        characterY += jumpSpeed;  // Gerakkan karakter ke atas
        jumpSpeed -= gravity;     // Mengurangi kecepatan lompatan karena gravitasi

        // Cek apakah karakter sudah mencapai puncak lompatan dan mulai turun
        if (jumpSpeed <= 0.0f) {
            isJumping = false;  // Hentikan lompatan ketika mencapai puncak
        }
    }
    else {
        // Jika karakter tidak melompat, gravitasi akan menarik karakter ke bawah
        if (characterY > -0.7f) {
            characterY -= gravity;  // Menarik karakter ke bawah secara bertahap
        }
        else {
            characterY = -0.7f;  // Menjaga agar karakter tidak jatuh di bawah tanah
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

    // Menggambar tanah (rumput hijau)
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
        characterY += jumpSpeed;  // Gerakkan karakter ke atas
        jumpSpeed -= gravity;     // Kurangi kecepatan dengan gravitasi
        if (characterY <= -0.7f) { // Jika karakter turun ke posisi awal
            characterY = -0.7f;
            isJumping = false;  // Hentikan lompatan
        }
    }

    // Update posisi karakter berdasarkan gravitasi dan lompatan
    updateJump();

    
    // Menggambar batu bata kecil yang tersusun ke atas di posisi awal
    drawBrickWall(-0.6f, -0.65f, 4, 2, 0.05f, 0.02f);

    // Menambahkan tumpukan batu baru di samping kanan dengan jarak 0.5 unit
    drawBrickWall(-0.1f, -0.65f, 4, 2, 0.05f, 0.02f); // Tumpukan pertama di kanan
    drawBrickWall(0.4f, -0.65f, 4, 2, 0.05f, 0.02f); // Tumpukan kedua di kanan


    // Karakter
    drawCharacter(characterX, characterY); // Tambahkan karakter di antara pohon

    // Logika lompatan
    if (isJumping) {
        characterY += jumpSpeed;  // Gerakkan karakter ke atas
        jumpSpeed -= gravity;     // Kurangi kecepatan dengan gravitasi
        if (characterY <= -0.7f) { // Jika karakter turun ke posisi awal
            characterY = -0.7f;
            isJumping = false;  // Hentikan lompatan
        }
    }

    // Draw two fairies at different positions in the sky
    drawFairy(-0.2f, 0.5f); // Left fairy
    drawFairy(0.3f, 0.6f);  // Right fairy
    drawFairy(-0.9f, 0.5f); // Left fairy
    drawFairy(0.4f, 0.8f);  // Right fairy

    cloudX1 += 0.0001f; // Kecepatan awan pertama
    cloudX2 += 0.0001f; // Kecepatan awan kedua
    cloudX3 += 0.0001f; // Kecepatan awan ketiga

    // Jika awan keluar dari layar di sisi kanan, kembalikan ke sisi kiri
    if (cloudX1 > 1.0f) { // Ubah dari -0.7f menjadi 1.0f
        cloudX1 = -0.5f; // Kembalikan awan pertama ke sisi kiri (ubah nilai ini)
    }
    if (cloudX2 > 1.0f) { // Ubah dari -0.7f menjadi 1.0f
        cloudX2 = -0.5f; // Kembalikan awan kedua ke sisi kiri (ubah nilai ini)
    }
    if (cloudX3 > 1.0f) { // Ubah dari -0.7f menjadi 1.0f
        cloudX3 = -0.5f; // Kembalikan awan ketiga ke sisi kiri (ubah nilai ini)
    }
    // Menggambar semua awan
    drawCloud(cloudX1, 0.6f); // Awan pertama
    drawCloud(cloudX2, 0.8f); // Awan kedua
    drawCloud(cloudX3, 0.7f); // Awan ketiga

    // Menambahkan matahari dengan sinar
    drawSun(-0.8f, 0.8f, 0.1f); 

   

    glutSwapBuffers(); // Menukar buffer agar tampilan diperbarui
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Warna latar belakang putih

    // Mengatur mode proyeksi dan mengatur sistem koordinat 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Pengaturan tampilan ortografis
   
}

int main(int argc, char** argv) {
    // Inisialisasi GLUT dan pengaturan jendela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600); 
    glutCreateWindow("Kerajaan dan Pemandangan Alam");
    glutKeyboardFunc(keyboard);
    init(); 

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop(); 
   

    return 0;
}