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
  unsigned char e1; // 0 = to rederect, 1 = end user.
  unsigned char e0;
  unsigned char ac;
} bin;

typedef struct {
  unsigned int id;
  unsigned char un[32];
  unsigned char ac;
} user;

bin *bins = NULL;
user *users = NULL;

unsigned int bin_len = 1024;
unsigned int user_len = 1024;

unsigned int s_bin = 0;
unsigned char e_bin = 0;

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

int log_value() {

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
}

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

unsigned int query(unsigned int id) {
  if (e_bin == 1) {
    if (users[s_bin - 1].id == id) {
      return s_bin;
    } else {
      printf("Error: did not find the requested id in database.\n");
      return 0;
    }
  }

  unsigned int pointe = s_bin;

  for (unsigned char lloo = 0; lloo < 255; lloo++) {

    if (get_bit(id, bins[pointe - 1].de) == 1) {
      if (bins[pointe - 1].e1 == 0) {
        pointe = bins[pointe - 1].a1;
      } else {
        if (users[bins[pointe - 1].a1 - 1].id == id) {
	  printf("[%d] :3\n",(int)lloo);
          return bins[pointe - 1].a1;
        } else {
          printf("Error: did not find the requested id in database.\n");
          return 0;
        }
      }
    } else {
      if (bins[pointe - 1].e0 == 0) {
        pointe = bins[pointe - 1].a0;
      } else {
        if (users[bins[pointe - 1].a0 - 1].id == id) {
	  printf("[%d]\n",(int)lloo);
          return bins[pointe - 1].a0;
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

unsigned int del_user(unsigned int id) {
  if (e_bin == 1) {
    //printf("monkey\n");
    if (users[s_bin - 1].id == id) {
      //return s_bin;
      //
      //
      users[s_bin - 1].ac = 0;

      s_bin = 0;
      e_bin = 0;

      

      return 1;

    } else {
      printf("Error: did not find the requested id in database. A\n");
      return 0;
    }
  }

  unsigned int pointe = s_bin;
  unsigned int histor = 0;
  unsigned char way = 0; //0 is 0 and 1 is 1, oviusly :(

  if(users[bins[pointe - 1].a1 - 1].id == id && bins[pointe - 1].e1 == 1){
    s_bin = bins[pointe - 1].a0;
    e_bin = bins[pointe - 1].e0;
    bins[pointe - 1].ac = 0;
    users[bins[pointe - 1].a1 - 1].ac = 0;
    return 1;
  }

  if(users[bins[pointe - 1].a0 - 1].id == id && bins[pointe - 1].e0 == 1){
    s_bin = bins[pointe - 1].a1;
    e_bin = bins[pointe - 1].e1;
    bins[pointe - 1].ac = 0;
    users[bins[pointe - 1].a0 - 1].ac = 0;
    return 1;
  }


  for (unsigned char lloo = 0; lloo < 255; lloo++) {

    if (get_bit(id, bins[pointe - 1].de) == 1) {
      if (bins[pointe - 1].e1 == 0) {
	histor = pointe;
	way = 1;
        pointe = bins[pointe - 1].a1;
      } else {
        if (users[bins[pointe - 1].a1 - 1].id == id) {
	  //printf("[%d] :3\n",(int)lloo);
          users[bins[pointe - 1].a1 - 1].ac = 0;
	  bins[pointe - 1].ac = 0;

	  if(way == 1){
	    bins[histor - 1].a1 = bins[pointe - 1].a0;
	    bins[histor - 1].e1 = bins[pointe - 1].e0;
 
	  }
	  else{
	    bins[histor - 1].a0 = bins[pointe - 1].a0;
	    bins[histor - 1].e0 = bins[pointe - 1].e0;

	  }

	  return 1;
        } else {
          printf("Error: did not find the requested id in database. B\n");
          return 0;
        }

	
      }

    } else {
      if (bins[pointe - 1].e0 == 0) {
	histor = pointe;
	way = 0;
        pointe = bins[pointe - 1].a0;
      } else {
        if (users[bins[pointe - 1].a0 - 1].id == id) {
	  //printf("[%d]\n",(int)lloo);
          //return bins[pointe - 1].a0;
	  //
	  //
	  users[bins[pointe - 1].a0 - 1].ac = 0;
	  bins[pointe - 1].ac = 0;

	  if(way == 1){
	    bins[histor - 1].a1 = bins[pointe - 1].a1;
	    bins[histor - 1].e1 = bins[pointe - 1].e1;
	  }
	  else{
	    bins[histor - 1].a0 = bins[pointe - 1].a1;
	    bins[histor - 1].e0 = bins[pointe - 1].e1;
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

unsigned int new_user(char *us) {

  unsigned int ids = 0;
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
    if (users[find_space].ac == 0) {
      //printf("found empty space at [%u] + 1\n", find_space);
      users[find_space].ac = 1;
      users[find_space].id = ids;
      strncpy(users[find_space].un, us, sizeof(users[find_space].un) - 1);
      //snprintf(users[find_space].un, sizeof(users[find_space].un), "%s", us);
      users[find_space].un[sizeof(users[find_space].un) - 1] = '\0';
      user_id = find_space + 1;
      break;
    }
  }

  if (user_id == 0) {
    printf("Error: did not find free space for a new user.\n");
    return 0;
  }

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

  // to handel if it is the first one to get added in the database.
  if (s_bin == 0) {
    s_bin = user_id;
    e_bin = 1;
    return ids;
  }

  unsigned int temp;
  unsigned int temp_swich;
  unsigned int curser = 0;
  //unsigned char deapth = 0;

  for (unsigned int find_swich = 0; find_swich < bin_len; find_swich++) {
    if (bins[find_swich].ac == 0) {
      temp_swich = find_swich + 1;
      bins[find_swich].ac = 1;

      break;
    }
  }

  if (temp_swich == 0) {
    printf("Error: did not find free space for a new bin.\n");
    return 0;
  }

  if(temp_swich >= bin_len - 1024){
    //printf("hit bin limit. (adding 1024 bins to data base.)\n");
    bin_len += 1024;
    //printf("bins %u\n",bin_len);
   

    bin *temp = realloc(bins,bin_len * sizeof(bin));

    if(!temp){
      printf("Error: out of memory.\n");
      free(bins);
      free(users);
      exit(0);
    }
    else{
      bins = temp;
    }


  }


  /*
    this part below are the branching algorithem that populates the tree.
    this part is currently wey broken and un optimized. (going to fix that
    later)










  */

  if (e_bin == 1) {

    diffs ll = diff(users[s_bin - 1].id, ids, 32);

    if (ll.point == 0) {
      printf("Error: somthing went wrong when mathing int's.\n");
      return 0;
    }

    // deapth = point - 1;
    temp = s_bin;

    s_bin = temp_swich;
    e_bin = 0;

    bins[s_bin - 1].de = ll.point - 1;
    bins[s_bin - 1].hi = ll.hist;

    if (get_bit(users[temp - 1].id, ll.point - 1) == 1) {
      bins[s_bin - 1].a1 = temp;
      bins[s_bin - 1].a0 = user_id;
    } else {
      bins[s_bin - 1].a0 = temp;
      bins[s_bin - 1].a1 = user_id;
    }

    bins[s_bin - 1].e0 = 1;
    bins[s_bin - 1].e1 = 1;

  } else { // 3th time and forword.

    if (bins[s_bin - 1].de != 0) {

      // for(unsigned char tryg = 0;tryg < 255;tryg++){
      //
      diffs ll = diff(bins[s_bin - 1].hi, ids, bins[s_bin - 1].de - 1);

      if (ll.point != 0) {

        //printf("erly bird.\n");

        // printf("Error: somthing went wrong when mathing int's.\n");
        // return 0;
        //
        //
        //
        temp = s_bin;

        s_bin = temp_swich;

        bins[s_bin - 1].de = ll.point - 1;
        bins[s_bin - 1].hi = ll.hist;

        if (get_bit(bins[temp - 1].hi, ll.point - 1) == 1) {
          bins[s_bin - 1].a1 = temp;
          bins[s_bin - 1].a0 = user_id;
          bins[s_bin - 1].e0 = 1;
        } else {
          bins[s_bin - 1].a0 = temp;
          bins[s_bin - 1].a1 = user_id;
          bins[s_bin - 1].e1 = 1;
        }

        return ids;

      } else {

        curser = s_bin; // not optimal to have multible parts that does the same
                        // thing.
      }
      //}

    } else {

      curser = s_bin;
    }

    //printf("my cur %u\n", curser - 1);
    /*unsigned char point = 0;
    unsigned int histor = 0;
    */

    for (unsigned char tryg = 0; tryg < 255; tryg++) {

      unsigned char *type; // = 0;
      unsigned int *sel;   //= 0;

      if (get_bit(ids, bins[curser - 1].de) == 1) {
        type = &bins[curser - 1].e1;
        sel = &bins[curser - 1].a1;
      } else {
        type = &bins[curser - 1].e0;
        sel = &bins[curser - 1].a0;
      }

      if (*type == 0) {
        diffs kk = diff(bins[*sel - 1].hi, ids,
                        bins[*sel - 1].de - 1); // -1 is the problem.

        if (kk.point == 0 || bins[*sel - 1].de - bins[curser - 1].de <= 1) {
          //printf("walking the lader\n");
          curser = *sel;
          continue;
        }
        if (kk.point != 0 && bins[*sel - 1].de - bins[curser - 1].de >= 2) {

          //printf("[branch]\n");

          temp = *sel;

          *sel = temp_swich;

          bins[temp_swich - 1].de = kk.point - 1;
          bins[temp_swich - 1].hi = kk.hist;

          if (get_bit(bins[temp - 1].hi, kk.point - 1) == 1) {
            bins[temp_swich - 1].a1 = temp;
            bins[temp_swich - 1].a0 = user_id;
            bins[temp_swich - 1].e0 = 1;
          } else {
            bins[temp_swich - 1].a0 = temp;
            bins[temp_swich - 1].a1 = user_id;
            bins[temp_swich - 1].e1 = 1;
          }

          return ids;
        }

      } else {

        //printf("[split]\n");

        diffs gay = diff(users[*sel - 1].id, ids,
                         32); // problem !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        temp = *sel;

        *sel = temp_swich;
        *type = 0;

        bins[temp_swich - 1].de = gay.point - 1;
        bins[temp_swich - 1].hi = gay.hist;

        if (get_bit(users[temp - 1].id, gay.point - 1) == 1) {
          bins[temp_swich - 1].a1 = temp;
          bins[temp_swich - 1].a0 = user_id;
        } else {
          bins[temp_swich - 1].a0 = temp;
          bins[temp_swich - 1].a1 = user_id;
        }

        bins[temp_swich - 1].e0 = 1;
        bins[temp_swich - 1].e1 = 1;

        return ids;
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

  return ids;
}

int main() {
  srand(time(NULL));
  bins = malloc(sizeof(bin) * bin_len);
  users = malloc(sizeof(user) * user_len);

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

  for(unsigned int yyu = 0;yyu < 64;yyu++){
    new_user("a1");
  }

  //log_value();
  //unsigned int test = new_user("femboy");

  for(unsigned int yyu = 0;yyu < user_len;yyu++){
    if(users[yyu].ac == 1){
      log_value();
      del_user(users[yyu].id);
    }
  }

  log_value();
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

  free(bins);
  free(users);

  // Check bits at positions 0, 1, 2, and 3
  // printf("Bit 0: %d\n", get_bit(number, 0)); // Output: 1 (true)
  // printf("Bit 1: %d\n", get_bit(number, 1)); // Output: 0 (false)
  // printf("Bit 2: %d\n", get_bit(number, 2)); // Output: 1 (true)
  // printf("Bit 3: %d\n", get_bit(number, 3)); // Output: 1 (true)
  // printf("Bit 32: %d\n", get_bit(number, 32)); // Output: 0 (out-of-range

  return 0;
}
