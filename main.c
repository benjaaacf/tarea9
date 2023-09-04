#include "cola.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxString 50
#define maxBooks 100
#define maxReserves 10

typedef struct {
  char title[maxString];
  char author[maxString];
  char genre[maxString];
  char isbn[maxString];
  char location[maxString];
  char status[maxString];
  char reserves[maxReserves][maxString];
  int num_reserves;
  char borrowed[maxString];
} Book;

Book library[maxBooks];
int numBooks = 0;

bool validateLength(const char *input, int max_length) {
  return (strlen(input) <= max_length);
}

void registerBook() {
  if (numBooks >= maxBooks) {
    printf("Libreria llena, no se pueden registrar mas libros.\n");
    return;
  }

  Book newBook;

  while (getchar() != '\n')
    ;

  do {
    printf("Ingrese titulo del libro: ");
    if (fgets(newBook.title, sizeof(newBook.title), stdin) == NULL) {
      printf("Error al leer la entrada.\n");
      exit(1);
    }
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    if (strlen(newBook.title) > maxString) {
      printf("Titulo demasiado largo. Debe tener como máximo %d caracteres.\n",
             maxString);
    }
  } while (strlen(newBook.title) > maxString);

  printf("Ingrese autor: ");
  if (fgets(newBook.author, sizeof(newBook.author), stdin) == NULL) {
    printf("Error al leer la entrada.\n");
    exit(1);
  }
  newBook.author[strcspn(newBook.author, "\n")] = '\0';

  while (strlen(newBook.author) > maxString) {
    printf("Autor invalido. Ingrese nuevamente: ");
    if (fgets(newBook.author, sizeof(newBook.author), stdin) == NULL) {
      printf("Error al leer la entrada.\n");
      exit(1);
    }
    newBook.author[strcspn(newBook.author, "\n")] = '\0';
  }

  printf("Ingrese genero: ");
  if (fgets(newBook.genre, sizeof(newBook.genre), stdin) == NULL) {
    printf("Error al leer la entrada.\n");
    exit(1);
  }
  newBook.genre[strcspn(newBook.genre, "\n")] = '\0';

  while (strlen(newBook.genre) > maxString) {
    printf("Genero invalido. Ingrese nuevamente: ");
    if (fgets(newBook.genre, sizeof(newBook.genre), stdin) == NULL) {
      printf("Error al leer la entrada.\n");
      exit(1);
    }
    newBook.genre[strcspn(newBook.genre, "\n")] = '\0';
  }

  printf("Ingrese ISBN: ");
  if (fgets(newBook.isbn, sizeof(newBook.isbn), stdin) == NULL) {
    printf("Error al leer la entrada.\n");
    exit(1);
  }
  newBook.isbn[strcspn(newBook.isbn, "\n")] = '\0';

  while (strlen(newBook.isbn) > maxString) {
    printf("ISBN invalido. Ingrese nuevamente: ");
    if (fgets(newBook.isbn, sizeof(newBook.isbn), stdin) == NULL) {
      printf("Error al leer la entrada.\n");
      exit(1);
    }
    newBook.isbn[strcspn(newBook.isbn, "\n")] = '\0';
  }

  printf("Ingrese ubicacion: ");
  if (fgets(newBook.location, sizeof(newBook.location), stdin) == NULL) {
    printf("Error al leer la entrada.\n");
    exit(1);
  }
  newBook.location[strcspn(newBook.location, "\n")] = '\0';

  while (strlen(newBook.location) > maxString) {
    printf("Ubicacion invalida. Ingrese nuevamente: ");
    if (fgets(newBook.location, sizeof(newBook.location), stdin) == NULL) {
      printf("Error al leer la entrada.\n");
      exit(1);
    }
    newBook.location[strcspn(newBook.location, "\n")] = '\0';
  }

  strcpy(newBook.status, "Disponible");
  newBook.num_reserves = 0;

  library[numBooks++] = newBook;

  printf("Registro completado!\n");
}

void showBookData() {
  char title[maxString];
  char author[maxString];

  printf("Ingrese titulo del libro: ");
  int result_title = scanf(" %[^\n]", title);

  printf("Ingrese autor: ");
  int result_author = scanf(" %[^\n]", author);

  if (result_title != 1 || result_author != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  for (int i = 0; i < numBooks; i++) {
    if (strcmp(library[i].title, title) == 0 &&
        strcmp(library[i].author, author) == 0) {
      printf("Titulo: %s\n", library[i].title);
      printf("Autor: %s\n", library[i].author);
      printf("Genero: %s\n", library[i].genre);
      printf("ISBN: %s\n", library[i].isbn);
      printf("Ubicacion: %s\n", library[i].location);
      printf("Estado: %s\n", library[i].status);
      if (library[i].num_reserves > 0) {
        printf("Reservas:\n");
        for (int j = 0; j < library[i].num_reserves; j++) {
          printf("  %s\n", library[i].reserves[j]);
        }
      }
      return;
    }
  }

  printf("Libro no encontrado.\n");
}

void showAllBooks() {
  if (numBooks == 0) {
    printf("No hay libros registrados.\n");
    return;
  }

  printf("Lista de todos los libros:\n");
  for (int i = 0; i < numBooks; i++) {
    printf("%s - %s\n", library[i].title, library[i].author);
  }
}

void reserveBook(Queue *reserveQueue) {
  char title[maxString];
  char author[maxString];
  char student[maxString];

  printf("Ingrese titulo del libro: ");
  if (scanf(" %[^\n]", title) != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  while (getchar() != '\n')
    ;

  printf("Ingrese autor: ");
  if (scanf(" %[^\n]", author) != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  printf("Ingrese nombre del estudiante: ");
  if (scanf(" %[^\n]", student) != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  for (int i = 0; i < numBooks; i++) {
    if (strcmp(library[i].title, title) == 0 &&
        strcmp(library[i].author, author) == 0) {
      if (strcmp(library[i].status, "Disponible") == 0) {
        strcpy(library[i].status, "Reservado");
        // Agregar a la cola
        enqueue(reserveQueue, student);
        printf("Reserva exitosa!\n");
      } else if (strcmp(library[i].status, "Reservado") == 0 ||
                 strcmp(library[i].status, "Prestado") == 0) {
        enqueue(reserveQueue, student);
        printf("Reserva exitosa!\n");
      } else {
        printf("El libro no puede ser reservado.\n");
      }
      return;
    }
  }

  printf("Libro no encontrado.\n");
}

void cancelReservation(Queue *reserveQueue) {
  char title[maxString];
  char author[maxString];
  char student[maxString];

  printf("Ingrese titulo del libro: ");
  if (scanf(" %[^\n]", title) != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  while (getchar() != '\n')
    ;

  printf("Ingrese autor: ");
  if (scanf(" %[^\n]", author) != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  printf("Ingrese nombre del estudiante: ");
  if (scanf(" %[^\n]", student) != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  for (int i = 0; i < numBooks; i++) {
    if (strcmp(library[i].title, title) == 0 &&
        strcmp(library[i].author, author) == 0) {
      if (!isQueueEmpty(reserveQueue)) {
        char reservedStudent[maxString];
        dequeue(reserveQueue, reservedStudent);

        if (strcmp(reservedStudent, student) == 0) {
          printf("Cancelacion de reserva exitosa!\n");
        } else {

          enqueue(reserveQueue, reservedStudent);
          printf("Reservacion no encontrada.\n");
        }
      } else {
        printf("Reservacion no encontrada.\n");
      }
      return;
    }
  }

  printf("Libro no encontrado.\n");
}

void borrowBook(Queue *reserveQueue) {
  char title[maxString];
  char author[maxString];
  char student[maxString];

  int result;

  printf("Ingrese titulo del libro: ");
  result = scanf(" %[^\n]", title);
  if (result != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  while (getchar() != '\n')
    ;

  printf("Ingrese autor: ");
  result = scanf(" %[^\n]", author);
  if (result != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  printf("Ingrese nombre del estudiante: ");
  result = scanf(" %[^\n]", student);
  if (result != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  for (int i = 0; i < numBooks; i++) {
    if (strcmp(library[i].title, title) == 0 &&
        strcmp(library[i].author, author) == 0) {
      if (strcmp(library[i].status, "Disponible") == 0) {
        strcpy(library[i].status, "Prestado");
        strcpy(library[i].borrowed, student);
        printf("Libro prestado con exito!\n");
      } else if (strcmp(library[i].status, "Reservado") == 0) {
        char reservedStudent[maxString];
        dequeue(reserveQueue, reservedStudent);

        if (strcmp(reservedStudent, student) == 0) {
          strcpy(library[i].status, "Prestado");
          strcpy(library[i].borrowed, student);
          printf("Libro prestado con exito!\n");
        } else {
          enqueue(reserveQueue, reservedStudent);
          printf("El libro no puede ser prestado.\n");
        }
      } else {
        printf("El libro no puede ser prestado.\n");
      }
      return;
    }
  }

  printf("Libro no encontrado.\n");
}

void returnBook(Queue *reserveQueue) {
  char title[maxString];
  char author[maxString];

  int result;

  printf("Ingrese titulo del libro: ");
  result = scanf(" %[^\n]", title);
  if (result != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  while (getchar() != '\n')
    ;

  printf("Ingrese autor: ");
  result = scanf(" %[^\n]", author);
  if (result != 1) {
    printf("Error al leer la entrada.\n");
    return;
  }

  for (int i = 0; i < numBooks; i++) {
    if (strcmp(library[i].title, title) == 0 &&
        strcmp(library[i].author, author) == 0) {
      if (!isQueueEmpty(reserveQueue)) {
        strcpy(library[i].status, "Reservado");
      } else {
        strcpy(library[i].status, "Disponible");
      }
      printf("Libro regresado exitosamente!\n");
      return;
    }
  }

  printf("Libro no encontrado.\n");
}

void showBorrowedBooks(Queue *reserveQueue) {
  int borrowed_count = 0;

  printf("Lista de libros prestados:\n");
  for (int i = 0; i < numBooks; i++) {
    if (strcmp(library[i].status, "Prestado") == 0) {
      borrowed_count++;
      printf("%s - %s (Prestado a %s)\n", library[i].title, library[i].author,
             library[i].borrowed);
    }
  }

  if (borrowed_count == 0) {
    printf("No se encuentran libros prestados.\n");
  }
}

void importBooks() {
  char filename[maxString];
  int result;
  printf("Ingrese nombre del archivo CSV: ");

  // Leer el valor y verificar la lectura
  result = scanf("%s", filename);
  if (result != 1) {
    printf("Error al leer el nombre del archivo.\n");
    return;
  }

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("No se puede abrir el archivo.\n");
    return;
  }

  char line[maxString * 7 + 6];
  while (fgets(line, sizeof(line), file) != NULL && numBooks < maxBooks) {
    Book newBook;
    sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", newBook.title,
           newBook.author, newBook.genre, newBook.isbn, newBook.location,
           newBook.status);

    if (strcmp(newBook.status, "Reserved") == 0 ||
        strcmp(newBook.status, "Borrowed") == 0) {
      int num_reserves;
      sscanf(line + strlen(newBook.title) + strlen(newBook.author) +
                 strlen(newBook.genre) + strlen(newBook.isbn) +
                 strlen(newBook.location) + strlen(newBook.status) + 6,
             ",%d", &num_reserves);
      newBook.num_reserves = num_reserves;

      // Leer los nombres de los estudiantes
      char studentName[maxString];
      for (int i = 0; i < num_reserves; i++) {
        sscanf(line + strlen(newBook.title) + strlen(newBook.author) +
                   strlen(newBook.genre) + strlen(newBook.isbn) +
                   strlen(newBook.location) + strlen(newBook.status) + 7 +
                   (i * (maxString + 1)),
               "%[^,\n]", studentName);
        strcpy(newBook.reserves[i], studentName);
      }
    } else {
      newBook.num_reserves = 0;
    }

    library[numBooks++] = newBook;
  }

  fclose(file);
  printf("Libros importados con éxito!\n");
}

void exportBooks() {
  char filename[maxString];
  printf("Ingrese nombre del archivo: ");
  int result = scanf("%s", filename);

  if (result != 1) {
    printf("Error al leer el nombre del archivo.\n");
    return;
  }

  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    printf("No se puede abrir el archivo.\n");
    return;
  }

  for (int i = 0; i < numBooks; i++) {
    fprintf(file, "%s,%s,%s,%s,%s,%s", library[i].title, library[i].author,
            library[i].genre, library[i].isbn, library[i].location,
            library[i].status);

    if (strcmp(library[i].status, "Reservado") == 0 ||
        strcmp(library[i].status, "Prestado") == 0) {
      fprintf(file, ",%d", library[i].num_reserves);
      for (int j = 0; j < library[i].num_reserves; j++) {
        fprintf(file, ",%s", library[i].reserves[j]);
      }
    }

    fprintf(file, "\n");
  }

  fclose(file);
  printf("Libros exportados con exito!\n");
}

int main() {
  int choice;

  Queue reserveQueue;
  initQueue(&reserveQueue);

  do {
    printf("\nSistema de biblioteca\n\n");
    printf("1. Registrar libro\n");
    printf("2. Datos del libro\n");
    printf("3. Mostrar todos los libros\n");
    printf("4. Reservar libro\n");
    printf("5. Cancelar reservacion\n");
    printf("6. Prestar libro\n");
    printf("7. Regresar libro\n");
    printf("8. Mostrar libros prestados\n");
    printf("9. Importar libros (Incluir .csv)\n");
    printf("10.Exportar libros (Incluir .csv)\n");
    printf("0. Salir\n\n");
    printf("Ingrese una opcion: ");

    int result = scanf("%d", &choice);

    if (result != 1) {
      printf("Error al leer la opcion.\n");
      break;
    }

    switch (choice) {
    case 1:
      registerBook();
      break;
    case 2:
      showBookData();
      break;
    case 3:
      showAllBooks();
      break;
    case 4:
      reserveBook(&reserveQueue);
      break;
    case 5:
      cancelReservation(&reserveQueue);
      break;
    case 6:
      borrowBook(&reserveQueue);
      break;
    case 7:
      returnBook(&reserveQueue);
      break;
    case 8:
      showBorrowedBooks(&reserveQueue);
      break;
    case 9:
      importBooks();
      break;
    case 10:
      exportBooks();
      break;
    case 0:
      printf("Saliendo...\n");
      break;
    default:
      printf("\nOpcion invalida, intente nuevamente.\n");
    }
  } while (choice != 0);

  return 0;
}