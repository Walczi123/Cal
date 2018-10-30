#include "Functions.h"

const double PI = 3.141592653589793238463;

void AddWindowText(HWND h, std::string text)
{
	int length = GetWindowTextLength(h);
	LPSTR buffer = (LPSTR)GlobalAlloc(GPTR, length + 1);
	GetWindowText(h, buffer, length + 1);
	int size = text.length();
	char * write = new char[length + size + 1];
	std::string s(buffer);
	s += text;
	SetWindowText(h, s.c_str());
	GlobalFree(buffer);
	delete[] write;
	return;
}

void LessWindowText(HWND h)
{
	int length = GetWindowTextLength(h);
	int i;
	if (length) {
		LPSTR buffer = (LPSTR)GlobalAlloc(GPTR, length + 1);
		GetWindowText(h, buffer, length);
		char * write = new char[length];
		for (i = 0; i < length - 1; i++) {
			write[i] = (char)buffer[i];
		}
		write[i] = '\0';
		SetWindowText(h, write);
	}
	return;
}

void NullWindowText(HWND h1, HWND h2)
{
	if(GetWindowTextLength(h1))SetWindowText(h1, "");
	if(GetWindowTextLength(h2))SetWindowText(h2, "");
	return;
}

unsigned int priority(std::string op)
{
	if (op == "(") { return 0; }
	else {
		if (op == "+" || op == "-" || op == ")") { return 1; }
		else {
			if (op == "*" || op == "/") { return 2; }
			else {
				if (op == "^") { return 3; }
				else { return -1; }
			}
		}
	}
}

std::string read_num(std::string text)
{
	std::string t = "";
	int dot = 0;
	if (text.length() != 0)
	{
		int i = 0;
		t = text;
		for (i = 0; i < text.length(); i++) {
			if (text[i] == '.')dot++;
			if (!isdigit(text[i]) && text[i] != '.') { break; }
			if (dot > 1) { break; }
		}
		t.erase(i, text.length() - 1);
	}
	return t;
}

std::deque<std::string> ONP( HWND hwnd , HWND err)
{
	int length = GetWindowTextLength(hwnd), i = 0, f1, f2, j;
	LPSTR buffer = (LPSTR)GlobalAlloc(GPTR, length + 1);
	GetWindowText(hwnd, buffer, length + 1);
	std::string e(buffer), n1,n2;
	GlobalFree(buffer);
	std::deque<std::string> deq_str, oper, tmp;
	if (e.length() == 0) {
		std::string s = "Error - there is no number to compute";
		MessageBox(err, s.c_str(), "Error - no number", MB_ICONINFORMATION);
		deq_str.push_front("ERR");
		return deq_str;
	}
	if (e[0] == '-')
	{
		e.erase(0, 1);
		n1 = "ERR";
		n1 = "-" + read_num(e);
		if (!n1.empty())deq_str.push_back(n1);
		e.erase(i, n1.length());
	}
	for (; e.length() > 0; i++)
	{
		if (e[i] == ' ') {
			e.erase(i, 1);
			i = -1;
		}
		else {
			if (isdigit(e[i])) {
				n1 = "ERR";
				n1 = read_num(e);
				if (!n1.empty())deq_str.push_back(n1);
				e.erase(i, n1.length());
				i = -1;
			}
			else {
				if (e[i] == '('&& e[i + 1] == '-')
				{
					e.erase(i, 2);
					n1 = "ERR";
					n1 = "-" + read_num(e);
					if (!n1.empty())deq_str.push_back(n1);
					e.erase(i, n1.length());
					i = -1;
				}
				else {
					if (e[i] == '(') {
						oper.push_front("("); // std::to_string(e[i])=ASCII('('); the function cannot be used here;
						e.erase(i, 1);
						i = -1;
					}
					else {
						if (e[i] == '+') {
							if (oper.empty() || priority("+") > priority(oper.front())) { oper.push_front("+"); } // std::to_string(e[i])=43; the function cannot be used here;
							else {
								for (std::string op : oper) {
									if (priority(op) >= priority("+"))
									{
										deq_str.push_back(op);
										oper.pop_front();
									}
									else { break; }
								}
								oper.push_front("+");
							}
							e.erase(i, 1);
							i = -1;
						}
						else {
							if (e[i] == '-')
							{
								if (oper.empty() || priority("-") > priority(oper.front())) { oper.push_front("-"); }
								else {
									for (auto& op : oper) {
										if (priority(op) >= priority("-"))
										{
											deq_str.push_back(op);
											oper.pop_front();
										}
										else { break; }
									}
									oper.push_front("-");
								}
								e.erase(i, 1);
								i = -1;
							}
							else {
								if (e[i] == ')')
								{
									for (auto& op : oper) {
										if (op != "(")
										{
											deq_str.push_back(op);
											oper.pop_front();
										}
										else
										{
											oper.pop_front();
											break;
										}
									}
									e.erase(i, 1);
									i = -1;
								}
								else {
									if (e[i] == '*')
									{
										if (oper.empty() || priority("*") > priority(oper.front())) { oper.push_front("*"); }
										else {
											for (auto& op : oper) {
												if (priority(op) >= priority("*"))
												{
													deq_str.push_back(op);
													oper.pop_front();
												}
												else { break; }
											}
											oper.push_front("*");
										}
										e.erase(i, 1);
										i = -1;
									}
									else {
										if (e[i] == '/')
										{
											if ((oper.empty() || priority("/") > priority(oper.front()))) { oper.push_front("/"); }
											else {
												for (auto& op : oper) {
													if (priority(op) >= priority("/"))
													{
														deq_str.push_back(op);
														oper.pop_front();
													}
													else { break; }
												}
												oper.push_front("/");
											}
											e.erase(i, 1);
											i = -1;
										}
										else {
											if (e[i] == '^')
											{
												if ((oper.empty() || priority("^") > priority(oper.front()))) { oper.push_front("^"); }
												else {
													for (auto& op : oper) {
														if (priority(op) >= priority("^"))
														{
															deq_str.push_back(op);
															oper.pop_front();
														}
														else { break; }
													}
													oper.push_front("^");
												}
												e.erase(i, 1);
												i = -1;
											}
											else {
												if (e[i] == '.')
												{
													e.erase(i, 1);
													n1 = "ERR";
													n1 = read_num(e);
													e.erase(i, n1.length());
													deq_str.push_back("ERR");
													MessageBox(err, "Error - incorect dot", "Error", MB_ICONINFORMATION);
													deq_str.push_front("ERR");
													return deq_str;
												}
												else {
													if (e[i] == 's'&&i<(e.length()-3)&&e[i+1] == 'i'&&e[i+2]=='n')
													{
														if(e[i + 3]=='(') 
														{
															e.erase(i, 3);
															f1 = f2 = 0;
															for (j = 0; j < e.length(); j++)
															{
																if (e[j] == '(')f1++;
																if (e[j] == ')')f2++;
																if (f1 == f2)break;
															}
															n1 = e;
															if (f1>f2)j = n1.length()-1;
															if(j!=n1.length()-1)n1.erase(j+1, n1.length() - 1);
															if(n1!=e)e.erase(0, n1.length());
															else e = "";
															tmp = ONP(n1, err);
															for (auto& t : tmp) {
																deq_str.push_back(t);
																tmp.pop_front();
															}
															deq_str.push_back("sin");
															i = -1;
														}
														else {
															e.erase(i, 3);
															n1 = "ERR";
															n1 = read_num(e);
															e.erase(i, n1.length());
															deq_str.push_back(n1);
															deq_str.push_back("sin");
															i = -1;
														}
													}
													else {
														if (e[i] == 'c'&&i < (e.length() - 3) && e[i + 1] == 'o'&&e[i + 2] == 's')
														{
															if (e[i + 3] == '(')
															{
																e.erase(i, 3);
																f1 = f2 = 0;
																for (j = 0; j < e.length(); j++)
																{
																	if (e[j] == '(')f1++;
																	if (e[j] == ')')f2++;
																	if (f1 == f2)break;
																}
																n1 = e;
																if (f1 > f2)j = n1.length() - 1;
																if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																if (n1 != e)e.erase(0, n1.length());
																else e = "";
																tmp = ONP(n1, err);
																for (auto& t : tmp) {
																	deq_str.push_back(t);
																	tmp.pop_front();
																}
																deq_str.push_back("cos");
																i = -1;
															}
															else {
																e.erase(i, 3);
																n1 = "ERR";
																n1 = read_num(e);
																e.erase(i, n1.length());
																deq_str.push_back(n1);
																deq_str.push_back("cos");
																i = -1;
															}
														}
														else {
															if (e[i] == 't'&&i < (e.length() - 3) && e[i + 1] == 'a'&&e[i + 2] == 'n')
															{
																if (e[i + 3] == '(')
																{
																	e.erase(i, 3);
																	f1 = f2 = 0;
																	for (j = 0; j < e.length(); j++)
																	{
																		if (e[j] == '(')f1++;
																		if (e[j] == ')')f2++;
																		if (f1 == f2)break;
																	}
																	n1 = e;
																	if (f1 > f2)j = n1.length() - 1;
																	if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																	if (n1 != e)e.erase(0, n1.length());
																	else e = "";
																	tmp = ONP(n1, err);
																	for (auto& t : tmp) {
																		deq_str.push_back(t);
																		tmp.pop_front();
																	}
																	deq_str.push_back("tan");
																	i = -1;
																}
																else {
																	e.erase(i, 3);
																	n1 = "ERR";
																	n1 = read_num(e);
																	e.erase(i, n1.length());
																	deq_str.push_back(n1);
																	deq_str.push_back("tan");
																	i = -1;
																}
															}
															else {
																if (e[i] == 'l'&&i < (e.length() - 3) && e[i + 1] == 'o'&&e[i + 2] == 'g')
																{
																	if (e[i + 3] == '(')
																	{
																		e.erase(i, 3);
																		f1 = f2 = 0;
																		for (j = 0; j < e.length(); j++)
																		{
																			if (e[j] == '(')f1++;
																			if (e[j] == ')')f2++;
																			if (f1 == f2)break;
																		}
																		n1 = e;
																		if (f1 > f2)j = n1.length() - 1;
																		if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																		if (n1 != e)e.erase(0, n1.length());
																		else e = "";
																		tmp = ONP(n1, err);
																		for (auto& t : tmp) {
																			deq_str.push_back(t);
																			tmp.pop_front();
																		}
																		deq_str.push_back("10");
																		deq_str.push_back("log");
																		i = -1;
																	}
																	else {
																		e.erase(i, 3);
																		n2 = "ERR";
																		n2 = read_num(e);
																		e.erase(i, n2.length());
																		if (e[0] == '(') {
																			f1 = f2 = 0;
																			for (j = 0; j < e.length(); j++)
																			{
																				if (e[j] == '(')f1++;
																				if (e[j] == ')')f2++;
																				if (f1 == f2)break;
																			}
																			n1 = e;
																			if (f1 > f2)j = n1.length() - 1;
																			if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																			if (n1 != e)e.erase(0, n1.length());
																			else e = "";
																			tmp = ONP(n1, err);
																			for (auto& t : tmp) {
																				deq_str.push_back(t);
																				tmp.pop_front();
																			}
																			deq_str.push_back(n2);
																			deq_str.push_back("log");
																			i = -1;
																		}
																		else {
																			deq_str.push_back(n2);
																			deq_str.push_back("10");
																			deq_str.push_back("log");
																			i = -1;
																		}
																	}
																}
																else {
																	if (e[i] == 'l'&&i <= (e.length() - 2) && e[i + 1] == 'n')
																	{
																		if (e[i + 2] == '(')
																		{
																			e.erase(i, 2);
																			f1 = f2 = 0;
																			for (j = 0; j < e.length(); j++)
																			{
																				if (e[j] == '(')f1++;
																				if (e[j] == ')')f2++;
																				if (f1 == f2)break;
																			}
																			n1 = e;
																			if (f1 > f2)j = n1.length() - 1;
																			if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																			if (n1 != e)e.erase(0, n1.length());
																			else e = "";
																			tmp = ONP(n1, err);
																			for (auto& t : tmp) {
																				deq_str.push_back(t);
																				tmp.pop_front();
																			}
																			deq_str.push_back("ln");
																			i = -1;
																		}
																		else {
																			e.erase(i, 2);
																			n1 = "ERR";
																			n1 = read_num(e);
																			e.erase(i, n1.length());
																			deq_str.push_back(n1);
																			deq_str.push_back("ln");
																			i = -1;
																		}
																	}
																	else {
																		if (e[i] == 'e')
																		{
																			deq_str.push_back(std::to_string(exp(1)));
																			e.erase(i,1);
																			i = -1;
																		}
																		else {
																			if (e[i] == 'p'&&i <= (e.length() - 2) && e[i + 1] == 'i')
																			{
																				deq_str.push_back(std::to_string(PI));
																				e.erase(i, 2);
																				i = -1;
																			}
																			else {
																				if (i < (e.length() - 5) && e[i] == 'r'&& e[i + 1] == 'o'&& e[i + 2] == 'o'&& e[i + 3] == 't')
																				{
																					e.erase(i, 4);
																					n2 = "ERR";
																					n2 = read_num(e);
																					e.erase(i, n2.length());
																					if (e[0] == '(') {
																						f1 = f2 = 0;
																						for (j = 0; j < e.length(); j++)
																						{
																							if (e[j] == '(')f1++;
																							if (e[j] == ')')f2++;
																							if (f1 == f2)break;
																						}
																						n1 = e;
																						if (f1 > f2)j = n1.length() - 1;
																						if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																						if (n1 != e)e.erase(0, n1.length());
																						else e = "";
																						tmp = ONP(n1, err);
																						for (auto& t : tmp) {
																							deq_str.push_back(t);
																							tmp.pop_front();
																						}
																						deq_str.push_back(std::to_string(1 / stod(n2)));
																						deq_str.push_back("^");
																						i = -1;
																					}
																					else {
																						std::string s = "Error - root is undefined \" " + e[i]; s += " \" ";
																						MessageBox(err, s.c_str(), "Error - root", MB_ICONINFORMATION);
																						deq_str.push_front("ERR");
																						return deq_str;
																					}
																				}
																				else {
																					if (e[i]='!')
																					{
																						deq_str.push_back("!");
																						e.erase(i, 1);
																						i = -1;
																					}
																					else {
																						std::string s = "Error - operator is undefined \" " + e[i]; s += " \" ";
																						MessageBox(err, s.c_str(), "Error - operator", MB_ICONINFORMATION);
																						deq_str.push_front("ERR");
																						e.erase(i, 1);
																						return deq_str;
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for (auto& op : oper) {
		if(op!="(")deq_str.push_back(op);
		oper.pop_front();
	}
	return deq_str;
};

std::deque<std::string> ONP(std::string e, HWND err)
{
	int i = 0,f1,f2,j;
	std::string n1,n2;
	std::deque<std::string> deq_str, oper, tmp;
	if (e.length() == 0) {
		std::string s = "Error - there is no number to compute";
		MessageBox(err, s.c_str(), "Error - no number", MB_ICONINFORMATION);
		deq_str.push_front("ERR");
		return deq_str;
	}
	if (e[0] == '-')
	{
		e.erase(0, 1);
		n1 = "ERR";
		n1 = "-" + read_num(e);
		if (!n1.empty())deq_str.push_back(n1);
		e.erase(i, n1.length());
	}
	for (; e.length() > 0; i++)
	{
		if (e[i] == ' ') {
			e.erase(i, 1);
			i = -1;
		}
		else {
			if (isdigit(e[i])) {
				n1 = "ERR";
				n1 = read_num(e);
				if (!n1.empty())deq_str.push_back(n1);
				e.erase(i, n1.length());
				i = -1;
			}
			else {
				if (e[i] == '('&& e[i + 1] == '-')
				{
					e.erase(i, 2);
					n1 = "ERR";
					n1 = "-" + read_num(e);
					if (!n1.empty())deq_str.push_back(n1);
					e.erase(i, n1.length());
					i = -1;
				}
				else {
					if (e[i] == '(') {
						oper.push_front("("); // std::to_string(e[i])=ASCII('('); the function cannot be used here;
						e.erase(i, 1);
						i = -1;
					}
					else {
						if (e[i] == '+') {
							if (oper.empty() || priority("+") > priority(oper.front())) { oper.push_front("+"); } // std::to_string(e[i])=43; the function cannot be used here;
							else {
								for (std::string op : oper) {
									if (priority(op) >= priority("+"))
									{
										deq_str.push_back(op);
										oper.pop_front();
									}
									else { break; }
								}
								oper.push_front("+");
							}
							e.erase(i, 1);
							i = -1;
						}
						else {
							if (e[i] == '-')
							{
								if (oper.empty() || priority("-") > priority(oper.front())) { oper.push_front("-"); }
								else {
									for (auto& op : oper) {
										if (priority(op) >= priority("-"))
										{
											deq_str.push_back(op);
											oper.pop_front();
										}
										else { break; }
									}
									oper.push_front("-");
								}
								e.erase(i, 1);
								i = -1;
							}
							else {
								if (e[i] == ')')
								{
									for (auto& op : oper) {
										if (op != "(")
										{
											deq_str.push_back(op);
											oper.pop_front();
										}
										else
										{
											oper.pop_front();
											break;
										}
									}
									e.erase(i, 1);
									i = -1;
								}
								else {
									if (e[i] == '*')
									{
										if (oper.empty() || priority("*") > priority(oper.front())) { oper.push_front("*"); }
										else {
											for (auto& op : oper) {
												if (priority(op) >= priority("*"))
												{
													deq_str.push_back(op);
													oper.pop_front();
												}
												else { break; }
											}
											oper.push_front("*");
										}
										e.erase(i, 1);
										i = -1;
									}
									else {
										if (e[i] == '/')
										{
											if ((oper.empty() || priority("/") > priority(oper.front()))) { oper.push_front("/"); }
											else {
												for (auto& op : oper) {
													if (priority(op) >= priority("/"))
													{
														deq_str.push_back(op);
														oper.pop_front();
													}
													else { break; }
												}
												oper.push_front("/");
											}
											e.erase(i, 1);
											i = -1;
										}
										else {
											if (e[i] == '^')
											{
												if ((oper.empty() || priority("^") > priority(oper.front()))) { oper.push_front("^"); }
												else {
													for (auto& op : oper) {
														if (priority(op) >= priority("^"))
														{
															deq_str.push_back(op);
															oper.pop_front();
														}
														else { break; }
													}
													oper.push_front("^");
												}
												e.erase(i, 1);
												i = -1;
											}
											else {
												if (e[i] == '.')
												{
													e.erase(i, 1);
													n1 = "ERR";
													n1 = read_num(e);
													e.erase(i, n1.length());
													deq_str.push_back("ERR");
													MessageBox(err, "Error - incorect dot", "Error", MB_ICONINFORMATION);
													i = -1;
												}
												else {
													if (e[i] == 's'&&i < (e.length() - 3) && e[i + 1] == 'i'&&e[i + 2] == 'n')
													{
														if (e[i + 3] == '(')
														{
															e.erase(i, 3);
															f1 = f2 = 0;
															for (j = 0; j < e.length(); j++)
															{
																if (e[j] == '(')f1++;
																if (e[j] == ')')f2++;
																if (f1 == f2)break;
															}
															n1 = e;
															if (f1 > f2)j = n1.length() - 1;
															if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
															if (n1 != e)e.erase(0, n1.length());
															else e = "";
															tmp = ONP(n1, err);
															for (auto& t : tmp) {
																deq_str.push_back(t);
																tmp.pop_front();
															}
															deq_str.push_back("sin");
															i = -1;
														}
														else {
															e.erase(i, 3);
															n1 = "ERR";
															n1 = read_num(e);
															e.erase(i, n1.length());
															deq_str.push_back(n1);
															deq_str.push_back("sin");
															i = -1;
														}
													}
													else {
														if (e[i] == 'c'&&i < (e.length() - 3) && e[i + 1] == 'o'&&e[i + 2] == 's')
														{
															if (e[i + 3] == '(')
															{
																e.erase(i, 3);
																f1 = f2 = 0;
																for (j = 0; j < e.length(); j++)
																{
																	if (e[j] == '(')f1++;
																	if (e[j] == ')')f2++;
																	if (f1 == f2)break;
																}
																n1 = e;
																if (f1 > f2)j = n1.length() - 1;
																if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																if (n1 != e)e.erase(0, n1.length());
																else e = "";
																tmp = ONP(n1, err);
																for (auto& t : tmp) {
																	deq_str.push_back(t);
																	tmp.pop_front();
																}
																deq_str.push_back("cos");
																i = -1;
															}
															else {
																e.erase(i, 3);
																n1 = "ERR";
																n1 = read_num(e);
																e.erase(i, n1.length());
																deq_str.push_back(n1);
																deq_str.push_back("cos");
																i = -1;
															}
														}
														else {
															if (e[i] == 't'&&i < (e.length() - 3) && e[i + 1] == 'a'&&e[i + 2] == 'n')
															{
																if (e[i + 3] == '(')
																{
																	e.erase(i, 3);
																	f1 = f2 = 0;
																	for (j = 0; j < e.length(); j++)
																	{
																		if (e[j] == '(')f1++;
																		if (e[j] == ')')f2++;
																		if (f1 == f2)break;
																	}
																	n1 = e;
																	if (f1 > f2)j = n1.length() - 1;
																	if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																	if (n1 != e)e.erase(0, n1.length());
																	else e = "";
																	tmp = ONP(n1, err);
																	for (auto& t : tmp) {
																		deq_str.push_back(t);
																		tmp.pop_front();
																	}
																	deq_str.push_back("tan");
																	i = -1;
																}
																else {
																	e.erase(i, 3);
																	n1 = "ERR";
																	n1 = read_num(e);
																	e.erase(i, n1.length());
																	deq_str.push_back(n1);
																	deq_str.push_back("tan");
																	i = -1;
																}
															}
															else {
																if (e[i] == 'l'&&i < (e.length() - 3) && e[i + 1] == 'o'&&e[i + 2] == 'g')
																{
																	if (e[i + 3] == '(')
																	{
																		e.erase(i, 3);
																		f1 = f2 = 0;
																		for (j = 0; j < e.length(); j++)
																		{
																			if (e[j] == '(')f1++;
																			if (e[j] == ')')f2++;
																			if (f1 == f2)break;
																		}
																		n1 = e;
																		if (f1 > f2)j = n1.length() - 1;
																		if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																		if (n1 != e)e.erase(0, n1.length());
																		else e = "";
																		tmp = ONP(n1, err);
																		for (auto& t : tmp) {
																			deq_str.push_back(t);
																			tmp.pop_front();
																		}
																		deq_str.push_back("10");
																		deq_str.push_back("log");
																		i = -1;
																	}
																	else {
																		e.erase(i, 3);
																		n2 = "ERR";
																		n2 = read_num(e);
																		e.erase(i, n2.length());
																		if (e[0] == '(') {
																			f1 = f2 = 0;
																			for (j = 0; j < e.length(); j++)
																			{
																				if (e[j] == '(')f1++;
																				if (e[j] == ')')f2++;
																				if (f1 == f2)break;
																			}
																			n1 = e;
																			if (f1 > f2)j = n1.length() - 1;
																			if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																			if (n1 != e)e.erase(0, n1.length());
																			else e = "";
																			tmp = ONP(n1, err);
																			for (auto& t : tmp) {
																				deq_str.push_back(t);
																				tmp.pop_front();
																			}
																			deq_str.push_back(n2);
																			deq_str.push_back("log");
																			i = -1;
																		}
																		else {
																			deq_str.push_back(n2);
																			deq_str.push_back("10");
																			deq_str.push_back("log");
																			i = -1;
																		}
																	}
																}
																else {
																	if (e[i] == 'l'&&i <= (e.length() - 2) && e[i + 1] == 'n')
																	{
																		if (e[i + 2] == '(')
																		{
																			e.erase(i, 2);
																			f1 = f2 = 0;
																			for (j = 0; j < e.length(); j++)
																			{
																				if (e[j] == '(')f1++;
																				if (e[j] == ')')f2++;
																				if (f1 == f2)break;
																			}
																			n1 = e;
																			if (f1 > f2)j = n1.length() - 1;
																			if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																			if (n1 != e)e.erase(0, n1.length());
																			else e = "";
																			tmp = ONP(n1, err);
																			for (auto& t : tmp) {
																				deq_str.push_back(t);
																				tmp.pop_front();
																			}
																			deq_str.push_back("ln");
																			i = -1;
																		}
																		else {
																			e.erase(i, 2);
																			n1 = "ERR";
																			n1 = read_num(e);
																			e.erase(i, n1.length());
																			deq_str.push_back(n1);
																			deq_str.push_back("ln");
																			i = -1;
																		}
																	}
																	else {
																		if (e[i] == 'e')
																		{
																			deq_str.push_back(std::to_string(exp(1)));
																			e.erase(i, 1);
																			i = -1;
																		}
																		else {
																			if (e[i] == 'p'&&i <= (e.length() - 2) && e[i + 1] == 'i')
																			{
																				deq_str.push_back(std::to_string(PI));
																				e.erase(i, 2);
																				i = -1;
																			}
																			else {
																				if (i < (e.length() - 5) && e[i] == 'r'&& e[i + 1] == 'o'&& e[i + 2] == 'o'&& e[i + 3] == 't')
																				{
																					e.erase(i, 4);
																					n2 = "ERR";
																					n2 = read_num(e);
																					e.erase(i, n2.length());
																					if (e[0] == '(') {
																						f1 = f2 = 0;
																						for (j = 0; j < e.length(); j++)
																						{
																							if (e[j] == '(')f1++;
																							if (e[j] == ')')f2++;
																							if (f1 == f2)break;
																						}
																						n1 = e;
																						if (f1 > f2)j = n1.length() - 1;
																						if (j != n1.length() - 1)n1.erase(j + 1, n1.length() - 1);
																						if (n1 != e)e.erase(0, n1.length());
																						else e = "";
																						tmp = ONP(n1, err);
																						for (auto& t : tmp) {
																							deq_str.push_back(t);
																							tmp.pop_front();
																						}
																						deq_str.push_back(std::to_string(1 / stod(n2)));
																						deq_str.push_back("^");
																						i = -1;
																					}
																					else {
																						std::string s = "Error - root is undefined \" " + e[i]; s += " \" ";
																						MessageBox(err, s.c_str(), "Error - root", MB_ICONINFORMATION);
																						deq_str.push_front("ERR");
																						return deq_str;
																					}
																				}
																				else {
																					if (e[i] = '!')
																					{
																						deq_str.push_back("!");
																						e.erase(i, 1);
																						i = -1;
																					}
																					else {
																						std::string s = "Error - operator is undefined \" " + e[i]; s += " \" ";
																						MessageBox(err, s.c_str(), "Error - operator", MB_ICONINFORMATION);
																						deq_str.push_front("ERR");
																						e.erase(i, 1);
																						return deq_str;
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for (auto& op : oper) {
		if (op != "(")deq_str.push_back(op);
		oper.pop_front();
	}
	return deq_str;
};

std::string Result (std::deque<std::string> deq_str, HWND err)
{
	double part;
	std::deque<std::string>::iterator it = deq_str.begin();
	while (deq_str.size() != 1)
	{
		if (*it == "ERR")
		{
			MessageBox(err, "Error Result", "Error", MB_ICONINFORMATION);
			return "Error res";
		}
		else {
			if (*it == "+")
			{
				part = stod(*(it - 2)) + stod(*(it - 1));
				*(it - 2) = std::to_string(part);
				deq_str.erase(it - 1, it + 1);
				it = deq_str.begin();
			}
			else {
				if (*it == "-")
				{
					part = stod(*(it - 2)) - stod(*(it - 1));
					*(it - 2) = std::to_string(part);
					deq_str.erase(it - 1, it + 1);
					it = deq_str.begin();
				}
				else {
					if (*it == "*")
					{
						part = stod(*(it - 2)) * stod(*(it - 1));
						*(it - 2) = std::to_string(part);
						deq_str.erase(it - 1, it + 1);
						it = deq_str.begin();
					}
					else {
						if (*it == "/")
						{
							if (stod(*(it - 1)) == 0.0) 
							{ 
								MessageBox(err, "Error Result", "Divided by 0", MB_ICONINFORMATION);
								return "Error div by 0";
							}
							part = stod(*(it - 2)) / stod(*(it - 1));
							*(it - 2) = std::to_string(part);
							deq_str.erase(it - 1, it + 1);
							it = deq_str.begin();
						}
						else {
							if (*it == "^")
							{
								part = pow(stod(*(it - 2)), stod(*(it - 1)));
								*(it - 2) = std::to_string(part);
								deq_str.erase(it - 1, it + 1);
								it = deq_str.begin();
							}
							else {
								if (*it == "sin")
								{
									part = sin(stod(*(it - 1)));
									*(it - 1) = std::to_string(part);
									deq_str.erase(it);
									it = deq_str.begin();
								}
								else {
									if (*it == "cos")
									{
										part = cos(stod(*(it - 1)));
										*(it - 1) = std::to_string(part);
										deq_str.erase(it);
										it = deq_str.begin();
									}
									else {
										if (*it == "tan")
										{
											part = tan(stod(*(it - 1)));
											*(it - 1) = std::to_string(part);
											deq_str.erase(it);
											it = deq_str.begin();
										}
										else {
											if (*it == "log")
											{
												part = log(stod(*(it - 1)), stod(*(it - 2)));
												*(it - 2) = std::to_string(part);
												deq_str.erase(it - 1, it + 1);
												it = deq_str.begin();
											}
											else {
												if (*it == "ln")
												{
													part = log(exp(1), stod(*(it - 1)));
													*(it - 1) = std::to_string(part);
													deq_str.erase(it);
													it = deq_str.begin();
												}
												else {
													if (*it == "!")
													{
														part = factorial(stod(*(it - 1)));
														*(it - 1) = std::to_string(part);
														deq_str.erase(it);
														it = deq_str.begin();
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		it++;
	}
	while(true)
	{
		if ((*deq_str.begin())[(*deq_str.begin()).length() - 1] == '.') { (*deq_str.begin()).erase((*deq_str.begin()).length() - 1); break; }
		if ((*deq_str.begin())[(*deq_str.begin()).length() - 1] == '0')(*deq_str.begin()).erase((*deq_str.begin()).length() - 1);
		else break;
	}
	return *deq_str.begin();
};

std::string Ans(HWND hwnd)
{
	int length = GetWindowTextLength(hwnd), i = 0;
	LPSTR buffer = (LPSTR)GlobalAlloc(GPTR, length + 1);
	GetWindowText(hwnd, buffer, length + 1);
	std::string e(buffer);
	GlobalFree(buffer);
	return e;
}

double log(double b, double e)
{
	return log(e) / log(b);
}

double factorial(double n)
{
	if (n < 0)return 0;
	if (n < 2)return 1;
	return (n*factorial(n - 1));
}