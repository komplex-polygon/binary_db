#include <limits.h> // For CHAR_BIT
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
  unsigned int
      a0; // 0 = NULL, the id has a +1 offcet so 0 is not a valid number.
  unsigned int a1;  // to get the real id you need to subtract by 1 (-1).
  unsigned char de; // deapth of the check. example: 0 for the first and 2 for
                    // the third bool.
  unsigned int hi;
  unsigned int e1; // 0 = to rederect, 1 = end user.
  unsigned int e0;
  unsigned char ac;
} u_int_bin;

typedef struct {
  unsigned int
      a0; // 0 = NULL, the id has a +1 offcet so 0 is not a valid number.
  unsigned int a1;  // to get the real id you need to subtract by 1 (-1).
  unsigned char de; // deapth of the check. example: 0 for the first and 2 for
                    // the third bool.
  unsigned char hi[32];
  unsigned char e1; // 0 = to rederect, 1 = end user.
  unsigned char e0;
  unsigned char ac;
} char_bin;

typedef struct {
  unsigned int id;
  unsigned char un[32];
  unsigned char ac;
} user;

typedef struct {
  user *bin;
  unsigned int len;
} user_db;

typedef struct {
  u_int_bin *bin;
  unsigned int len;
  unsigned int s;// = 0;
  unsigned int e;// = 0;
} u_int_index;

typedef struct {
  char_bin *bin;
  unsigned int len;
  unsigned int s;// = 0;
  unsigned int e;// = 0;
} char_index;



//bin *bins = NULL;
//user *users = NULL;

//unsigned int bin_len = 1024;
//unsigned int user_len = 1024;

//unsigned int s_bin = 0;
//unsigned char e_bin = 0;

unsigned int new_user(user_db *b){
  
  unsigned int user_id = 0;

  for (unsigned int find_space = 0; find_space < b -> len; find_space++) {
    if(b -> bin[find_space].ac == 0) {
      //printf("found empty space at [%u] + 1\n", find_space);
      b -> bin[find_space].ac = 1;
      //users[find_space].id = ids;
      //strncpy(users[find_space].un, us, sizeof(users[find_space].un) - 1);
      //snprintf(users[find_space].un, sizeof(users[find_space].un), "%s", us);
      //users[find_space].un[sizeof(users[find_space].un) - 1] = '\0';
      user_id = find_space + 1;
      break;
    }
  }  


  if(user_id >= b -> len - 3){
    //printf("hit user limit. (adding 1024 users to data base.)\n");
    b -> len += 1024;
    //printf("users %u\n",user_len);

    user *temp = realloc(b -> bin,b -> len * sizeof(user));

    if(!temp){
      printf("Error: out of memory.\n");
      //free(bins);
      //free(users);
      exit(0);
    }
    else{
      b -> bin = temp;
    }

  }

  return user_id;
}

int get_bit(unsigned int value, unsigned int position) {
  // Calculate the total number of bits in an unsigned int
  const unsigned int total_bits = sizeof(value) * CHAR_BIT;

  // Check if the requested position is within valid bounds
  if (position < total_bits) {
    // Shift the target bit to the LSB position and isolate it
    return (value >> position) & 1;
  }
  // Return 0 for positions beyond the size of the type
  return 0;
}

unsigned int generate_random_uint(void) {
  unsigned int result = 0;
  for (size_t i = 0; i < sizeof(unsigned int); i++) {
    // Shift existing bits left by 8, then OR with a new random byte
    result = (result << 8) | (rand() & 0xFF);
  }
  return result;
}


user_db new_db() {
  user_db temp = {0};
  temp.len = 1024;
  temp.bin = malloc(sizeof(user) * 1024); 
  return temp;
}

u_int_index new_u_int_index_db() {
  u_int_index temp = {0};
  temp.len = 1024;
  temp.bin = malloc(sizeof(u_int_bin) * 1024); 
  return temp;
}

char_index new_char_index_db() {
  char_index temp = {0};
  temp.len = 1024;
  temp.bin = malloc(sizeof(char_bin) * 1024); 
  return temp;
}


/*int log_value() {

  printf("[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
  printf("  s_bin = %u, e_bin = %d\n", s_bin - 1, (int)e_bin);
  printf("[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");

  for (unsigned int bindd = 0; bindd < bin_len; bindd++) {
    if (bins[bindd].ac == 1) {
      printf("(%2u) [id:00000,a0:%u,a1:%u,e0:%u,e1:%u,hi:%u,de:%u]\n", bindd,
             bins[bindd].a0 - 1, bins[bindd].a1 - 1, bins[bindd].e0,
             bins[bindd].e1, bins[bindd].hi, bins[bindd].de);
    }
  }

  printf("[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");

  for (unsigned int ubindd = 0; ubindd < user_len; ubindd++) {
    if (users[ubindd].ac == 1) {
      printf("(%2u) [id:%10u,", ubindd, users[ubindd].id);
      for (unsigned char bits = 32; bits > 0; bits--) {
        printf("%d", get_bit(users[ubindd].id, bits - 1));
      }
      printf("]\n");
    }
  }

  printf("[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n\n\n");

  return 1;
}*/

typedef struct {
  unsigned char point;
  unsigned int hist;
} diffs;

diffs diff(unsigned int a, unsigned int b, unsigned char len) {
  // unsigned char point = 0;
  // unsigned int histor = 0;
  //
  //printf("A:%u,B:%u,len:%d\n", a, b, (int)len);

  diffs jj = {0};
  for (unsigned char gf = 0; gf < len; gf++) {

    if (get_bit(a, gf) == get_bit(b, gf)) {
      if (get_bit(b, gf) == 1) {
        jj.hist += pow(2, gf); // uppgrade aftervords. wery inafithion. :3
        //printf(":1 %u\n", jj.hist);
      } else {
        //printf(":0\n");
      }
    } else {
      //printf("id mathing at [%d]\n", (int)gf);
      jj.point = gf + 1;
      break;
    }
  }

  /*if(jj.point == 0){
      printf("Error: somthing went wrong when mathing int's.\n");
  }*/

  return jj;
}

unsigned int query_u_int_index(u_int_index a,unsigned int id) {
  if (a.e != 0) {
    if (a.e == id) {
      return a.s;
    } else {
      printf("Error: did not find the requested id in database.\n");
      return 0;
    }
  }

  unsigned int pointe = a.s;

  for (unsigned char lloo = 0; lloo < 255; lloo++) {

    if (get_bit(id, a.bin[pointe - 1].de) == 1) {
      if (a.bin[pointe - 1].e1 == 0) {
        pointe = a.bin[pointe - 1].a1;
      } else {
        if (a.bin[pointe - 1].e1 == id) {
	  printf("[%d] :3\n",(int)lloo);
          return a.bin[pointe - 1].a1;
        } else {
          printf("Error: did not find the requested id in database.\n");
          return 0;
        }
      }
    } else {
      if (a.bin[pointe - 1].e0 == 0) {
        pointe = a.bin[pointe - 1].a0;
      } else {
        if (a.bin[pointe - 1].e0 == id) {
	  printf("[%d]\n",(int)lloo);
          return a.bin[pointe - 1].a0;
        } else {
          printf("Error: did not find the requested id in database.\n");
          return 0;
        }
      }
    }
  }
  printf("Error: did not find the requested id in database.\n");
  return 0;
}

unsigned int del_u_int_index(u_int_index *a,unsigned int id) {
  if (a -> e != 0) {
    //printf("monkey\n");
    if (a -> e == id) {
      //return s_bin;
      //
      //
      //b -> bin[a -> s - 1].ac = 0;

      a -> s = 0;
      a -> e = 0;

      

      return 1;

    } else {
      printf("Error: did not find the requested id in database. A\n");
      return 0;
    }
  }

  unsigned int pointe = a -> s;
  unsigned int histor = 0;
  unsigned char way = 0; //0 is 0 and 1 is 1, oviusly :(

  if(a -> bin[pointe - 1].e1 == id){
    a -> s = a -> bin[pointe - 1].a0;
    a -> e = a -> bin[pointe - 1].e0;
    a -> bin[pointe - 1].ac = 0;
    //b -> bin[a -> bin[pointe - 1].a1 - 1].ac = 0;
    return 1;
  }

  if(a -> bin[pointe - 1].e0 == id){
    a -> s = a -> bin[pointe - 1].a1;
    a -> e = a -> bin[pointe - 1].e1;
    a -> bin[pointe - 1].ac = 0;
    //b -> bin[a -> bin[pointe - 1].a0 - 1].ac = 0;
    return 1;
  }


  for (unsigned char lloo = 0; lloo < 255; lloo++) {

    if (get_bit(id, a -> bin[pointe - 1].de) == 1) {
      if (a -> bin[pointe - 1].e1 == 0) {
	histor = pointe;
	way = 1;
        pointe = a -> bin[pointe - 1].a1;
      } else {
        if (a -> bin[pointe - 1].e1 == id) {
	  //printf("[%d] :3\n",(int)lloo);
          //b -> bin[a -> bin[pointe - 1].a1 - 1].ac = 0;
	  a -> bin[pointe - 1].ac = 0;

	  if(way == 1){
	    a -> bin[histor - 1].a1 = a -> bin[pointe - 1].a0;
	    a -> bin[histor - 1].e1 = a -> bin[pointe - 1].e0;
 
	  }
	  else{
	    a -> bin[histor - 1].a0 = a -> bin[pointe - 1].a0;
	    a -> bin[histor - 1].e0 = a -> bin[pointe - 1].e0;

	  }

	  return 1;
        } else {
          printf("Error: did not find the requested id in database. B\n");
          return 0;
        }

	
      }

    } else {
      if (a -> bin[pointe - 1].e0 == 0) {
	histor = pointe;
	way = 0;
        pointe = a -> bin[pointe - 1].a0;
      } else {
        if (a -> bin[pointe - 1].e0 == id) {
	  //printf("[%d]\n",(int)lloo);
          //return bins[pointe - 1].a0;
	  //
	  //
	  //b -> bin[a -> bin[pointe - 1].a0 - 1].ac = 0;
	  a -> bin[pointe - 1].ac = 0;

	  if(way == 1){
	    a -> bin[histor - 1].a1 = a -> bin[pointe - 1].a1;
	    a -> bin[histor - 1].e1 = a -> bin[pointe - 1].e1;
	  }
	  else{
	    a -> bin[histor - 1].a0 = a -> bin[pointe - 1].a1;
	    a -> bin[histor - 1].e0 = a -> bin[pointe - 1].e1;
	  }

	  return 1;	  

        } else {
          printf("Error: did not find the requested id in database. C\n");
          return 0;
        }

	//way = 0;
      }

    }
  }
  printf("Error: did not find the requested id in database. D\n");
  return 0;
}

unsigned int new_u_int_index(u_int_index *a,unsigned int id,unsigned int path) {

  /*unsigned int ids = 0;
  unsigned char found_id = 0;

  for (unsigned char trys = 0; trys < 255; trys++) {

    unsigned int new_id = generate_random_uint();

    unsigned char is_free = 1;

    for (unsigned int find_id = 0; find_id < user_len; find_id++) {

      if (users[find_id].ac == 1 && users[find_id].id == new_id) {
        is_free = 0;
        break;
      }
    }

    if (is_free == 1) {

      ids = new_id;
      found_id = 1;
      //printf("found free id [%u]\n", new_id);
      break;
    } else {
      printf("try [%d/255]\n", (int)trys);
    }
  }

  if (found_id == 0) {
    printf("Error: did not find a free id within 255 trys.\n");
    return 0;
  }

  // if still 0 means not faund a emty space:
  unsigned int user_id = 0;

  for (unsigned int find_space = 0; find_space < user_len; find_space++) {
    if(users[find_space].ac == 0) {
      //printf("found empty space at [%u] + 1\n", find_space);
      users[find_space].ac = 1;
      users[find_space].id = ids;§§
      strncpy(users[find_space].un, us, sizeof(users[find_space].un) - 1);
      //snprintf(users[find_space].un, sizeof(users[find_space].un), "%s", us);
      users[find_space].un[sizeof(users[find_space].un) - 1] = '\0';
      user_id = find_space + 1;
      break;
    }
  }

  */

  if (path == 0) {
    printf("Error: invalid path.\n");
    return 0;
  }

  /*

  if(user_id >= user_len - 1024){
    //printf("hit user limit. (adding 1024 users to data base.)\n");
    user_len += 1024;
    //printf("users %u\n",user_len);

    user *temp = realloc(users,user_len * sizeof(user));

    if(!temp){
      printf("Error: out of memory.\n");
      free(bins);
      free(users);
      exit(0);
    }
    else{
      users = temp;
    }

  }

  */

  // to handel if it is the first one to get added in the database.
  if (a -> s == 0) {
    a -> s = path;
    a -> e = id;
    return 1;
  }

  unsigned int temp;
  unsigned int temp_e;
  unsigned int temp_swich;
  unsigned int curser = 0;
  //unsigned char deapth = 0;

  for (unsigned int find_swich = 0; find_swich < a -> len; find_swich++) {
    if (a -> bin[find_swich].ac == 0) {
      temp_swich = find_swich + 1;
      a -> bin[find_swich].ac = 1;

      break;
    }
  }

  if (temp_swich == 0) {
    printf("Error: did not find free space for a new bin.\n");
    return 0;
  }

  if(temp_swich >= a -> len - 3){
    //printf("hit bin limit. (adding 1024 bins to data base.)\n");
    a -> len += 1024;
    //printf("bins %u\n",bin_len);
   

    u_int_bin *temp = realloc(a -> bin,a -> len * sizeof(u_int_bin));

    if(!temp){
      printf("Error: out of memory.\n");
      //free(a.bin);
      //free(b.bin);
      exit(0);
    }
    else{
      a -> bin = temp;
    }


  }


  /*
    this part below are the branching algorithem that populates the tree.
    this part is currently wey broken and un optimized. (going to fix that
    later)










  */

  if (a -> e != 0) {

    diffs ll = diff(a -> e/*b.bin[a -> s - 1].id*/, id, 32);

    if (ll.point == 0) {
      printf("Error: somthing went wrong when mathing int's.\n");
      return 0;
    }

    // deapth = point - 1;
    temp = a -> s;
    temp_e = a -> e;

    a -> s = temp_swich;
    a -> e = 0;

    a -> bin[a -> s - 1].de = ll.point - 1;
    a -> bin[a -> s - 1].hi = ll.hist;

    if (get_bit(temp_e, ll.point - 1) == 1) {
      a -> bin[a -> s - 1].a1 = temp;
      a -> bin[a -> s - 1].e1 = temp_e;
      a -> bin[a -> s - 1].a0 = path;
      a -> bin[a -> s - 1].e0 = id;
    } else {
      a -> bin[a -> s - 1].a0 = temp;
      a -> bin[a -> s - 1].e0 = temp_e;
      a -> bin[a -> s - 1].a1 = path;
      a -> bin[a -> s - 1].e1 = id;
    }

    //a -> bin[a -> s - 1].e0 = 1;
    //a -> bin[a -> s - 1].e1 = 1;

  } else { // 3th time and forword.

    if (a -> bin[a -> s - 1].de != 0) {

      // for(unsigned char tryg = 0;tryg < 255;tryg++){
      //
      diffs ll = diff(a -> bin[a -> s - 1].hi, id, a -> bin[a -> s - 1].de - 1);

      if (ll.point != 0) {

        //printf("erly bird.\n");

        // printf("Error: somthing went wrong when mathing int's.\n");
        // return 0;
        //
        //
        //
        temp = a -> s;
	temp_e = a -> e;

        a -> s = temp_swich;

        a -> bin[a -> s - 1].de = ll.point - 1;
        a -> bin[a -> s - 1].hi = ll.hist;

        if (get_bit(a -> bin[temp - 1].hi, ll.point - 1) == 1) {
          a -> bin[a -> s - 1].a1 = temp;
          a -> bin[a -> s - 1].a0 = path;
          a -> bin[a -> s - 1].e0 = id;
	  a -> bin[a -> s - 1].e1 = temp_e;
        } else {
          a -> bin[a -> s - 1].a0 = temp;
          a -> bin[a -> s - 1].a1 = path;
          a -> bin[a -> s - 1].e1 = id;
	  a -> bin[a -> s - 1].e0 = temp_e;
        }

        return 1;

      } else {

        curser = a -> s; // not optimal to have multible parts that does the same
                        // thing.
      }
      //}

    } else {

      curser = a -> s;
    }

    //printf("my cur %u\n", curser - 1);
    /*unsigned char point = 0;
    unsigned int histor = 0;
    */

    for (unsigned char tryg = 0; tryg < 255; tryg++) {

      unsigned int *type; // = 0;
      unsigned int *sel;   //= 0;

      if (get_bit(id, a -> bin[curser - 1].de) == 1) {
        type = &a -> bin[curser - 1].e1;
        sel = &a -> bin[curser - 1].a1;
      } else {
        type = &a -> bin[curser - 1].e0;
        sel = &a -> bin[curser - 1].a0;
      }

      if (*type == 0) {
        diffs kk = diff(a -> bin[*sel - 1].hi, id,
                        a -> bin[*sel - 1].de - 1); // -1 is the problem.

        if (kk.point == 0 || a -> bin[*sel - 1].de - a -> bin[curser - 1].de <= 1) {
          //printf("walking the lader\n");
          curser = *sel;
          continue;
        }
        if (kk.point != 0 && a -> bin[*sel - 1].de - a -> bin[curser - 1].de >= 2) {

          //printf("[branch]\n");

          temp = *sel;

          *sel = temp_swich;

          a -> bin[temp_swich - 1].de = kk.point - 1;
          a -> bin[temp_swich - 1].hi = kk.hist;

          if (get_bit(a -> bin[temp - 1].hi, kk.point - 1) == 1) {
            a -> bin[temp_swich - 1].a1 = temp;
            a -> bin[temp_swich - 1].a0 = path;
            a -> bin[temp_swich - 1].e0 = id;
          } else {
            a -> bin[temp_swich - 1].a0 = temp;
            a -> bin[temp_swich - 1].a1 = path;
            a -> bin[temp_swich - 1].e1 = id;
          }

          return 1;
        }

      } else {

        //printf("[split]\n");

        diffs gay = diff(*type, id,
                         32); // problem !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        temp = *sel;
	temp_e = *type;

        *sel = temp_swich;
        *type = 0;

        a -> bin[temp_swich - 1].de = gay.point - 1;
        a -> bin[temp_swich - 1].hi = gay.hist;

        if (get_bit(temp_e, gay.point - 1) == 1) {
          a -> bin[temp_swich - 1].a1 = temp;
          a -> bin[temp_swich - 1].a0 = path;
	  a -> bin[temp_swich - 1].e0 = id;
	  a -> bin[temp_swich - 1].e1 = temp_e;
        } else {
          a -> bin[temp_swich - 1].a0 = temp;
          a -> bin[temp_swich - 1].a1 = path;
	  a -> bin[temp_swich - 1].e1 = id;
	  a -> bin[temp_swich - 1].e0 = temp_e;
        }

        

        return 1;
      }
    }
    /*

    for(unsigned char gf = 0;gf < 16;gf++){

      if(get_bit(users[s_bin - 1].id,gf) == get_bit(ids,gf)){
        if(get_bit(ids,gf) == 1){
          histor += pow(2,gf);  //uppgrade aftervords. wery inafithion. :3
          printf(":1 %u\n",histor);
        }
        else{
          printf(":0\n");
        }
      }
      else{
        printf("id mathing at [%d]\n",(int) gf);
        point = gf + 1;
        break;
      }
    }

    if(point == 0){
      printf("Error: somthing went wrong when mathing int's.\n");
      return 0;
    }
  }

  //deapth = point - 1;
  temp = s_bin;

  s_bin = temp_swich;
  e_bin = 0;

  bins[s_bin - 1].de = point - 1;
  bins[s_bin - 1].hi = histor;

  if(get_bit(users[temp - 1].id,point - 1) == 1){
    bins[s_bin - 1].a1 = temp;
    bins[s_bin - 1].a0 = user_id;
  }
  else{
    bins[s_bin - 1].a0 = temp;
    bins[s_bin - 1].a1 = user_id;
  }
  */
  }

  return 0;
}

int main() {
  srand(time(NULL));
  //bins = malloc(sizeof(bin) * bin_len);
  //users = malloc(sizeof(user) * user_len);

  // unsigned int number = 1;  // Binary: 1101 (LSB: 1, bit0)

  /*log_value();

  new_user();

  log_value();

  new_user();

  log_value();

  new_user();

  log_value();

  new_user();

  log_value();

  new_user(); // ko

  log_value();
  */

  /*for(unsigned int yyu = 0;yyu < 64;yyu++){
    new_user("a1");
  }*/

  //log_value();
  //unsigned int test = new_user("femboy");

  /*for(unsigned int yyu = 0;yyu < user_len;yyu++){
    if(users[yyu].ac == 1){
      log_value();
      del_user(users[yyu].id);
    }
  }

  log_value();*/
  /*log_value();

  new_user();

  log_value();

  new_user();

  log_value();

  new_user();
  */
  //log_value();
  

  //unsigned int test2 = query(test) - 1;

  //printf("\n[%s]\n\n",users[test2].un);

  //free(bins);
  //free(users);
  //
  //

   user_db b = new_db();

   u_int_index a = new_u_int_index_db();

  for(unsigned int yyu = 0;yyu < 64;yyu++){
    //new_user("a1");
    unsigned int test = new_user(&b);
    unsigned int id = yyu + 1; 
    b.bin[test - 1].id = id;

    strncpy(b.bin[test - 1].un, "Hello world.", sizeof(b.bin[test - 1].un) - 1);
    b.bin[test - 1].un[sizeof(b.bin[test - 1].id) - 1] = '\0';
    new_u_int_index(&a,id,test);
  }
    
   unsigned int test = query_u_int_index(a,32);
   printf("%u\n",test);

    //new_u_int_index()


  // Check bits at positions 0, 1, 2, and 3
  // printf("Bit 0: %d\n", get_bit(number, 0)); // Output: 1 (true)
  // printf("Bit 1: %d\n", get_bit(number, 1)); // Output: 0 (false)
  // printf("Bit 2: %d\n", get_bit(number, 2)); // Output: 1 (true)
  // printf("Bit 3: %d\n", get_bit(number, 3)); // Output: 1 (true)
  // printf("Bit 32: %d\n", get_bit(number, 32)); // Output: 0 (out-of-range

  return 0;
}
