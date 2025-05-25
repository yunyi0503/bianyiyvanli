#include "SyntaxAnalyse.hpp"
#include <cstring>
#include <memory>

extern ast::SyntaxTree syntax_tree;

void SyntaxAnalyseCompUnit(ast::compunit_syntax* &self, ast::compunit_syntax* compunit, ast::func_def_syntax* func_def) {
    if (compunit == nullptr) {
        self = new ast::compunit_syntax();
        self->global_defs.push_back(std::shared_ptr<ast::func_def_syntax>(func_def));
    } else {
        self = compunit;
        self->global_defs.push_back(std::shared_ptr<ast::func_def_syntax>(func_def));
    }
    syntax_tree.root = self;
}

void SyntaxAnalyseFuncDef(ast::func_def_syntax* &self, vartype var_type, char* Ident, ast::block_syntax* block) {
    self = new ast::func_def_syntax();
    self->rettype = var_type;
    self->name = Ident;
    self->body = std::shared_ptr<ast::block_syntax>(block);
}

void SynataxAnalyseFuncType(vartype &self, char* type) {
    if (strcmp(type, "int") == 0) {
        self = vartype::INT;
    } else {
        self = vartype::VOID;
    }
}

void SynataxAnalyseBlock(ast::block_syntax* &self, ast::block_syntax* block_items) {
    if (block_items == nullptr) {
        self = new ast::block_syntax();
    } else {
        self = block_items;
    }
}

void SynataxAnalyseBlockItems(ast::block_syntax* &self, ast::block_syntax* block_items, ast::stmt_syntax* stmt) {
    if (block_items == nullptr) {
        self = new ast::block_syntax();
        if (stmt != nullptr) {
            self->body.push_back(std::shared_ptr<ast::stmt_syntax>(stmt));
        }
    } else {
        self = block_items;
        if (stmt != nullptr) {
            self->body.push_back(std::shared_ptr<ast::stmt_syntax>(stmt));
        }
    }
}

void SynataxAnalyseStmtReturn(ast::stmt_syntax* &self, ast::expr_syntax* exp) {
    auto ret_stmt = new ast::return_stmt_syntax();
    ret_stmt->exp = std::shared_ptr<ast::expr_syntax>(exp);
    self = ret_stmt;
}

void SynataxAnalysePrimaryExpIntConst(ast::expr_syntax* &self, char* current_symbol) {
    auto int_const = new ast::literal_syntax();
    int_const->intConst = std::stoi(current_symbol);
    int_const->restype = vartype::INT;
    self = int_const;
}

void SynataxAnalyseStmtBlock(ast::stmt_syntax* &self, ast::block_syntax* block) {
    auto block_stmt = new ast::block_syntax();
    block_stmt->body = block->body;
    self = block_stmt;
}

void SynataxAnalysePrimaryExpVar(ast::expr_syntax* &self, char* current_symbol) {
    auto var_expr = new ast::lval_syntax();
    var_expr->name = current_symbol;
    var_expr->restype = vartype::INT;
    self = var_expr;
}

void SynataxAnalyseVarDecl(ast::stmt_syntax* &self, ast::var_def_stmt_syntax* var_def, ast::var_decl_stmt_syntax* var_def_group) {
    auto decl = new ast::var_decl_stmt_syntax();
    decl->var_def_list.push_back(std::shared_ptr<ast::var_def_stmt_syntax>(var_def));
    
    if (var_def_group) {
        for (auto &def : var_def_group->var_def_list) {
            decl->var_def_list.push_back(def);
        }
    }
    
    self = decl;
}

void SynataxAnalyseVarDefGroup(ast::var_decl_stmt_syntax* &self, ast::var_def_stmt_syntax* var_def, ast::var_decl_stmt_syntax* var_def_group) {
    if (var_def_group == nullptr) {
        self = new ast::var_decl_stmt_syntax();
        self->var_def_list.push_back(std::shared_ptr<ast::var_def_stmt_syntax>(var_def));
    } else {
        auto new_group = new ast::var_decl_stmt_syntax();
        new_group->var_def_list.push_back(std::shared_ptr<ast::var_def_stmt_syntax>(var_def));
        
        for (auto &def : var_def_group->var_def_list) {
            new_group->var_def_list.push_back(def);
        }
        
        self = new_group;
    }
}

void SynataxAnalyseVarDef(ast::var_def_stmt_syntax* &self, char* ident, ast::expr_syntax* init) {
    self = new ast::var_def_stmt_syntax();
    self->name = ident;
    self->initializer = std::shared_ptr<ast::expr_syntax>(init);
    self->restype = vartype::INT;
}

void SynataxAnalyseAddExp(ast::expr_syntax* &self, ast::expr_syntax* exp1, char* op, ast::expr_syntax* exp2) {
    auto bin_expr = new ast::binop_expr_syntax();
    bin_expr->lhs = std::shared_ptr<ast::expr_syntax>(exp1);
    bin_expr->rhs = std::shared_ptr<ast::expr_syntax>(exp2);
    if (strcmp(op, "+") == 0) {
        bin_expr->op = binop::plus;
    } else {
        bin_expr->op = binop::minus;
    }
    self = bin_expr;
}

void SynataxAnalyseMulExp(ast::expr_syntax* &self, ast::expr_syntax* exp1, char* op, ast::expr_syntax* exp2) {
    auto bin_expr = new ast::binop_expr_syntax();
    bin_expr->lhs = std::shared_ptr<ast::expr_syntax>(exp1);
    bin_expr->rhs = std::shared_ptr<ast::expr_syntax>(exp2);
    if (strcmp(op, "*") == 0) {
        bin_expr->op = binop::multiply;
    } else if (strcmp(op, "%") == 0) {
        bin_expr->op = binop::modulo;
    } else {
        bin_expr->op = binop::divide;
    }
    self = bin_expr;
}

void SynataxAnalyseStmtAssign(ast::stmt_syntax* &self, ast::lval_syntax* target, ast::expr_syntax* value) {
    auto assign_stmt = new ast::assign_stmt_syntax();
    assign_stmt->target = std::shared_ptr<ast::lval_syntax>(target);
    assign_stmt->value = std::shared_ptr<ast::expr_syntax>(value);
    self = assign_stmt;
}

void SynataxAnalyseLval(ast::lval_syntax* &self, char* ident) {
    self = new ast::lval_syntax();
    self->name = ident;
    self->restype = vartype::INT;
}

void SynataxAnalyseStmtIf(ast::stmt_syntax* &self, ast::expr_syntax* cond, ast::stmt_syntax* then_body, ast::stmt_syntax* else_body) {
    auto if_stmt = new ast::if_stmt_syntax();
    if_stmt->pred = std::shared_ptr<ast::expr_syntax>(cond);
    if_stmt->then_body = std::shared_ptr<ast::stmt_syntax>(then_body);
    if_stmt->else_body = std::shared_ptr<ast::stmt_syntax>(else_body);
    self = if_stmt;
}

void SynataxAnalyseLOrExp(ast::expr_syntax* &self, ast::expr_syntax* cond1, ast::expr_syntax* cond2) {
    auto logic_expr = new ast::logic_cond_syntax();
    logic_expr->op = relop::op_or;
    logic_expr->lhs = std::shared_ptr<ast::expr_syntax>(cond1);
    logic_expr->rhs = std::shared_ptr<ast::expr_syntax>(cond2);
    self = logic_expr;
}

void SynataxAnalyseLAndExp(ast::expr_syntax* &self, ast::expr_syntax* cond1, ast::expr_syntax* cond2) {
    auto logic_expr = new ast::logic_cond_syntax();
    logic_expr->op = relop::op_and;
    logic_expr->lhs = std::shared_ptr<ast::expr_syntax>(cond1);
    logic_expr->rhs = std::shared_ptr<ast::expr_syntax>(cond2);
    self = logic_expr;
}

void SynataxAnalyseEqExp(ast::expr_syntax* &self, ast::expr_syntax* cond1, char* op, ast::expr_syntax* cond2) {
    auto rel_expr = new ast::rel_cond_syntax();
    if (strcmp(op, "==") == 0) {
        rel_expr->op = relop::equal;
    } else {
        rel_expr->op = relop::non_equal;
    }
    rel_expr->lhs = std::shared_ptr<ast::expr_syntax>(cond1);
    rel_expr->rhs = std::shared_ptr<ast::expr_syntax>(cond2);
    self = rel_expr;
}

void SynataxAnalyseRelExp(ast::expr_syntax* &self, ast::expr_syntax* cond1, char* op, ast::expr_syntax* exp) {
    auto rel_expr = new ast::rel_cond_syntax();
    if (strcmp(op, "<") == 0) {
        rel_expr->op = relop::less;
    } else if (strcmp(op, ">") == 0) {
        rel_expr->op = relop::greater;
    } else if (strcmp(op, "<=") == 0) {
        rel_expr->op = relop::less_equal;
    } else {
        rel_expr->op = relop::greater_equal;
    }
    rel_expr->lhs = std::shared_ptr<ast::expr_syntax>(cond1);
    rel_expr->rhs = std::shared_ptr<ast::expr_syntax>(exp);
    self = rel_expr;
}

void SynataxAnalyseUnaryExp(ast::expr_syntax* &self, char* op, ast::expr_syntax* exp) {
    auto unary_expr = new ast::unaryop_expr_syntax();
    if (strcmp(op, "+") == 0) {
        unary_expr->op = unaryop::plus;
    } else if (strcmp(op, "-") == 0) {
        unary_expr->op = unaryop::minus;
    } else {
        unary_expr->op = unaryop::op_not;
    }
    unary_expr->rhs = std::shared_ptr<ast::expr_syntax>(exp);
    self = unary_expr;
}
