/* Menu atualizado */
/* Aqui indicamos ao usuário que a opção 4 é para avaliar um local.
   Explicação: a avaliação é restrita a usuários cadastrados, com nota de 5 a 10
   e comentário opcional de até 200 caracteres. Isso evita avaliações inválidas e
   mantém comentários curtos e objetivos para melhor visualização e armazenamento.
*//* Menu atualizado - opção de avaliação de local */
printf("%s4) Avaliar local (usuários cadastrados, nota 5-10, comentário 200 chars)%s\n", CLR_MAGENTA, CLR_RESET);

/* Avaliar local */
/* Função: rate_place()
   Objetivo: permitir que usuários cadastrados avaliem destinos turísticos.
   Funcionalidades implementadas:
   - Verifica se há usuários cadastrados.
   - Solicita nome de usuário e valida se está cadastrado.
   - Lista todos os destinos disponíveis para avaliação.
   - Permite ao usuário escolher o destino por ID.
   - Recebe nota de 5 a 10 e comentário opcional de até 200 caracteres.
   - Armazena a avaliação na lista e salva em arquivo (persistência).
   
   Possíveis melhorias futuras:
   1) Evitar que o mesmo usuário avalie o mesmo local mais de uma vez.
   2) Exibir média de avaliações de cada local após o cadastro de uma nota.
   3) Implementar verificação de conteúdo do comentário (palavras impróprias).
   4) Permitir edição ou exclusão de avaliações pelo próprio usuário.
   5) Mostrar avaliações anteriores de um local antes de adicionar a nova.
*/
void rate_place(){
    /* Verifica se existem usuários cadastrados */
    if (n_users == 0){ 
        printf("Nenhum usuário cadastrado. Cadastre-se primeiro.\n"); 
        return; 
    }

    /* Solicita nome de usuário */
    char uname[50];
    printf("Seu nome de usuário: ");
    if (scanf("%49s", uname) != 1){ 
        clear_stdin(); 
        printf("Entrada inválida.\n"); 
        return; 
    }
    clear_stdin();

    /* Valida se o usuário existe */
    int uid = find_user_by_username(uname);
    if (uid == -1){ 
        printf("Usuário não encontrado.\n"); 
        return; 
    }

    /* Lista todos os destinos disponíveis para o usuário escolher */
    list_all();

    /* Solicita ID do destino a avaliar e valida */
    printf("ID do local a avaliar: ");
    int did = read_int();
    if (did < 0 || did >= n_dest){ 
        printf("Destino inválido.\n"); 
        return; 
    }

    /* Solicita nota de avaliação entre 5 e 10 */
    int rating;
    printf("Nota (5-10): ");
    rating = read_int();
    if (rating < 5 || rating > 10){ 
        printf("Nota inválida. Use de 5 a 10.\n"); 
        return; 
    }

    /* Solicita comentário opcional até 200 caracteres */
    char comment[201];
    printf("Comentário (até 200 caracteres, opcional): ");
    fgets(comment, sizeof(comment), stdin); 
    comment[strcspn(comment, "\n")] = 0; /* Remove '\n' do final */

    /* Armazena a avaliação no array de ratings */
    ratings[n_ratings].user_id = uid;
    ratings[n_ratings].dest_id = did;
    ratings[n_ratings].rating = rating;
    strncpy(ratings[n_ratings].comment, comment, sizeof(ratings[n_ratings].comment)-1);
    n_ratings++;

    /* Salva avaliações no arquivo para persistência */
    save_ratings();

    printf(CLR_MAGENTA "Avaliação registrada com sucesso!\n" CLR_RESET);
}
