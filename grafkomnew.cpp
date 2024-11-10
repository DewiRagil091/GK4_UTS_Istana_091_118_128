#include <glut.h>
#include <cmath>

float characterX = -0.98f; // Posisi X karakter
float cloudX1 = -0.6f;
float cloudX2 = 0.0f;
float cloudX3 = 0.6f;

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


void drawFinishLine() {
    // Garis vertikal kiri
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f); 
    glVertex2f(-0.95f, -0.4f);
    glVertex2f(-0.95f, -1.0f);
    glEnd();

    // Garis vertikal kanan
    glBegin(GL_LINES);
    glVertex2f(0.95f, -0.4f); 
    glVertex2f(0.95f, -1.0f); 
    glEnd();
}

//menggammbar batu rintangan
void drawBrickWall(float x, float y, int rows, int columns, float brickWidth, float brickHeight) {
    glColor3f(0.5f, 0.4f, 0.2f);

    for (int i = 0; i < rows; i++) {
        float offsetX = (i % 2 == 0) ? 0.0f : brickWidth / 2.0f; // Offset untuk pola selang-seling
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
    glutPostRedisplay(); // Memperbarui tampilan
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

    // Menggambar garis finish
    drawFinishLine();

    // Menggambar istana atau bangunan kerajaan
    drawCastle(0.6f, -0.3f); 

    // Menambahkan 3 pohon  kecil yang berjejer dari kiri ke kanan
    drawTree(-0.8f, -0.3f); 
    drawTree(-0.4f, -0.3f);  
    drawTree(0.0f, -0.3f);  

    // Karakter
    drawCharacter(characterX, -0.7f); // Tambahkan karakter di antara pohon

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


    // Menggambar batu bata kecil yang tersusun ke atas di posisi awal
    drawBrickWall(-0.6f, -0.7f, 6, 3, 0.05f, 0.02f);

    // Menambahkan tumpukan batu baru di samping kanan dengan jarak 0.5 unit
    drawBrickWall(-0.1f, -0.7f, 6, 3, 0.05f, 0.02f); // Tumpukan pertama di kanan
    drawBrickWall(0.4f, -0.7f, 6, 3, 0.05f, 0.02f); // Tumpukan kedua di kanan



    glutSwapBuffers(); // Menukar buffer agar tampilan diperbarui
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Warna latar belakang putih

    // Mengatur mode proyeksi dan mengatur sistem koordinat 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Sistem koordinat 2D dengan ukuran -1.0 hingga 1.0
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